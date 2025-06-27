#ifndef AUDIO_HPP
#define AUDIO_HPP

#include  <string>
#include <vector>

struct AudioData {
    std::vector<float> samples;
    uint32_t sampleRate = 0;
    uint32_t channels   = 0;
};

inline std::string toLower(std::string s);

AudioData loadAudioFile(const std::string& path);

#endif