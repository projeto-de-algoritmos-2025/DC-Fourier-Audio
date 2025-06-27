#include <ranges>
#include <stdexcept>
#include <algorithm>
#include "dr_libs-master/dr_wav.h"
#include "dr_libs-master/dr_mp3.h"
#include "audio.hpp"

inline std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return s;
}

AudioData loadAudioFile(const std::string& path)
{
    AudioData out;
    const auto ext = toLower(path.substr(path.find_last_of('.') + 1));

    if (ext == "wav") {
        drwav wav;
        if (!drwav_init_file(&wav, path.c_str(), nullptr))
            throw std::runtime_error("dr_wav: cannot open file");

        out.channels   = wav.channels;
        out.sampleRate = wav.sampleRate;
        // 32-bit float decode in one call:
        out.samples.resize(static_cast<size_t>(wav.totalPCMFrameCount * wav.channels));
        drwav_read_pcm_frames_f32(&wav,
                                  wav.totalPCMFrameCount,
                                  out.samples.data());
        drwav_uninit(&wav);
    }
    else if (ext == "mp3") {
        drmp3 mp3;
        if (!drmp3_init_file(&mp3, path.c_str(), nullptr))
            throw std::runtime_error("dr_mp3: cannot open file");

        out.channels   = mp3.channels;
        out.sampleRate = mp3.sampleRate;
        drmp3_uint64 frameCount = drmp3_get_pcm_frame_count(&mp3);

        std::vector<int16_t> tmp(frameCount * mp3.channels);
        drmp3_read_pcm_frames_s16(&mp3, frameCount, tmp.data());
        drmp3_uninit(&mp3);

        // convert int16 → float −1.0 … 1.0
        out.samples.resize(tmp.size());
        const float scale = 1.0f / 32768.0f;
        for (size_t i = 0; i < tmp.size(); ++i)
            out.samples[i] = static_cast<float>(tmp[i]) * scale;
    }
    else {
        throw std::runtime_error("Unsupported extension: " + ext);
    }

    return out;
}