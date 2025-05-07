#include <math.h>
#include <vector>
#include "waveform.h"

namespace wf {
    const double SAMPLE_RATE {44100.f};
    const double TWOPI {6.283185307f};
    const short MAX_AMP {32767};
    const double EQUAL_T {1.05946f};

    void Scale::justIntonation(const double tonic) {
        double ji[] = {
            tonic, 
            tonic * (9.0/8), 
            tonic * (5.0/4), 
            tonic * (4.0/3),
            tonic * (3.0/2), 
            tonic * (5.0/3), 
            tonic * (15.0/8), 
            tonic * 2
        };
        for (double x : ji) {
            scale.push_back(x);
        }
    }

    void Scale::equalTemperament(const double tonic) {
        const double et[8] = {
            1.0,
            pow(EQUAL_T, 2),
            pow(EQUAL_T, 4),
            pow(EQUAL_T, 5),
            pow(EQUAL_T, 7),
            pow(EQUAL_T, 9),
            pow(EQUAL_T, 11),
            2.0
        };

        for (double x : et) {
            scale.push_back(tonic * x);
        }
    }

    short SineWave(int samplePart, double frequency, double amplitude) {
        double samplesPerCycle {SAMPLE_RATE / frequency};
        double cyclePart {samplePart / samplesPerCycle};
        double rad {TWOPI * cyclePart};
        short amp = static_cast<short>(MAX_AMP * amplitude);

        short result = static_cast<short>(amp * sin(rad));
        return result;
    }

    short SquareWave(int samplePart, double frequency, double amplitude) {
        int samplesPerCycle = static_cast<int>(SAMPLE_RATE / frequency);
        int cyclepart {samplePart % samplesPerCycle};
        int halfcycle {samplesPerCycle / 2};
        short amp = static_cast<short>(MAX_AMP * amplitude);

        short result = static_cast<short>(amp * -1);
        if (cyclepart < halfcycle) {
            result = amp;
        }
        return result;
    }

    short SawToothWave(int samplePart, double frequency, double amplitude) {
        int samplesPerCycle = static_cast<int>(SAMPLE_RATE / frequency);
        int cyclePart {samplePart % samplesPerCycle};
        double halfCycle {samplesPerCycle / 2.0};
        double amp {MAX_AMP * amplitude};

        double result {amp * ((cyclePart - halfCycle) / halfCycle)};
        
        return static_cast<short>(result);
    }

    short TriangleWave(int samplePart, double frequency, double amplitude) {
        int samplesPerCycle = static_cast<int>(SAMPLE_RATE / frequency);
        int cyclePart {samplePart % samplesPerCycle};
        double halfCycle {samplesPerCycle / 2.0};
        double qCycle {halfCycle / 2.0}; // Quarter of a cycle
        double amp {MAX_AMP * amplitude};

        double result;
        if (cyclePart < halfCycle) {
            result = amp * ((cyclePart - qCycle) / qCycle);
        } else {
            result = amp * (((halfCycle + qCycle) - cyclePart) / qCycle);
        }
        
        return static_cast<short>(result);
    }

    short WhiteNoise(double amplitude) {
        short amp = static_cast<short>(MAX_AMP * amplitude);
        short result = static_cast<short>(rand() % amp);
        return result;
    }
}