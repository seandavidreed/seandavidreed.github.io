#ifndef SOUND_H
#define SOUND_H

#include <math.h>

namespace sound {
    #define TWOPI 6.283185307
    #define SAMPLE_RATE 44100.0
    #define MAX_AMP 32767 // maximum positive value of signed short

    short SineWave(double time, double freq, double amp) {
        double tpc {SAMPLE_RATE / freq}; // ticks per cycle
        double cycles {time / tpc};
        double rad {TWOPI * cycles};
        short amplitude = static_cast<short>(MAX_AMP * amp);

        short result = static_cast<short>(amplitude * sin(rad));
        return result;
    }

    short SquareWave(double time, double freq, double amp) {
        int tpc = static_cast<int>(SAMPLE_RATE / freq); // ticks per cycle
        int cyclepart (static_cast<int>(time) % tpc);
        int halfcycle {tpc / 2};
        short amplitude = static_cast<short>(MAX_AMP * amp);

        short result {0};
        if (cyclepart < halfcycle) {
            result = amplitude;
        }
        return result;
    }

    short Noise(double amp) {
        short amplitude = static_cast<short>(MAX_AMP * amp);

        short result = static_cast<short>(rand() % amplitude);
        return result;
    }




}

#endif