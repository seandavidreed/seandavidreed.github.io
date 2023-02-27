#ifndef WAVEFORM_H
#define WAVEFORM_H

namespace wf {
    extern const double SAMPLE_RATE;
    extern const double TWOPI;
    extern const short MAX_AMP;

    class Scale { 
    public:
        std::vector<double> scale;
        void justIntonation(double tonic);
        void equalTemperament(double tonic);
    };

    short SineWave(int samplePart, double frequency, double amplitude);
    short SquareWave(int samplePart, double frequency, double amplitude);
    short SawToothWave(int samplePart, double frequency, double amplitude);
    short TriangleWave(int samplePart, double frequency, double amplitude);
    short WhiteNoise(double amplitude);
}

#endif