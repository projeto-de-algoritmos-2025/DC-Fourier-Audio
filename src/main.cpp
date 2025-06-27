#include <vector>
#include <math.h>
#include <complex>
#include "matplotlib/matplotlibcpp.h"
#include "audio.hpp"

using namespace std;
namespace plt = matplotlibcpp;
const double PI {acos(-1.0)};

void fft(vector<complex<double>>& xs, bool invert = false){
    int N = (int) xs.size();

    if (N == 1)
        return;

    vector<complex<double>> es(N/2), os(N/2);

    for (int i = 0; i < N/2; ++i)
        es[i] = xs[2*i];

    for (int i = 0; i < N/2; ++i)
        os[i] = xs[2*i + 1];

    fft(es, invert);
    fft(os, invert);

    auto signal = (invert ? 1 : -1);
    auto theta = 2 * signal * PI / N;
    complex<double> S { 1 }, S1 { cos(theta), sin(theta) };

    for (int i = 0; i < N/2; ++i)
    {
        xs[i] = (es[i] + S * os[i]);
        xs[i] /= (invert ? 2 : 1);

        xs[i + N/2] = (es[i] - S * os[i]);
        xs[i + N/2] /= (invert ? 2 : 1);

        S *= S1;
    }
}

int main(int argc, char** argv){
    if(argc < 2){
        cerr << "Audio file missing\n";
        exit(-1);
    }
    
    string path = argv[1];
    cout << "Loading audio...\n";
    AudioData data = loadAudioFile(path);

    int n = data.samples.size();
    double val = 0, rate = data.sampleRate;
    vector<double> x(n), y(n);
    vector<complex<double>> Fy(n);
    for(int i=0; i<n; ++i) {
        double t = i / rate;
        x[i] = t;
        y[i] = data.samples[i];
        Fy[i] = {y[i], 0};
    }
    cout << "Applying the transform...\n";
    fft(Fy);
    int nh = n / 2 + 1;
    double scale = 1.0 / n;
    vector<double> freq(nh), mag(nh);
    for(int i = 0; i < nh; i++){
        freq[i] = i*rate/n;
        mag[i] = 2.0*abs(Fy[i])/n;

    }
    // Set the size of output image to 1200x780 pixels
    plt::figure();  
    // Plot line from given x and y data. Color is selected automatically.
    plt::subplot(2, 1, 1);
    plt::plot(x, y);
    plt::xlabel("Time");
    plt::ylabel("Amplitude");
    plt::title("Time Series");


    plt::subplot(2, 1, 2);
    plt::plot(freq, mag);
    plt::xlim(0.0, 1000.0);
    plt::xlabel("Frequency");
    plt::ylabel("Magnitude");
    plt::title("Spectrum");


    // Enable legend.
    //plt::legend();
    plt::tight_layout();
    plt::show();
    return 0;
}