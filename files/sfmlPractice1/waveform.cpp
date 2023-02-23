#include <math.h>
#include "waveform.h"

namespace wf {
    const double SAMPLE_RATE {44100.f};
    const double TWOPI {6.283185307f};
    const short MAX_AMP {32767};

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