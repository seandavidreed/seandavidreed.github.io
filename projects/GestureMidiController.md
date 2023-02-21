# WebAssembly Gesture Controlled Synthesizer

### 2/19/2023
Today, I began brainstorming: how could I start a project that would have personal significance, practicability, and that would help solidify what I’m learning? Once again, synths and audio came to mind. After roaming the internet, I’ve decided to try to build a web application that can generate audio controlled by hand gestures! This file will document the research and build process. Here are the initial steps I've taken:

- Follow the WebAssembly tutorial on MDN Web Docs
- Research available open source audio I/O libraries for C++
  - Found SFML (Simple and Fast Multimedia Library), which was available through APT, by watching [this tutorial](https://youtube.com/playlist?list=PLSiFUSQSRYAM36UYQLEFGOAVf95rkQJXQ).

### 2/20/2023
I studied the program produced by yesterdays tutorial and I browsed the SFML API documentation. That familiar fog of unknowing hung around me as I puzzled through the SineWave function. Ultimately, I came to understand it, but I'm not sure I could replicate it from scratch yet. I made some changes to the function mainly to practice C++ syntax, e.g. adding static_cast<> to make any implicit conversions explicit, making  preprocessor directives for SAMPLE_RATE and MAX_AMP, using braced initialization.

```
// SAMPLE_RATE = 44100; MAX_AMP = 32767 (max positive value of signed short)
short SineWave(double time, double freq, double amp) {
        double tpc {SAMPLE_RATE / freq}; // ticks per cycle
        double cycles {time / tpc};
        double rad {TWOPI * cycles};
        short amplitude = static_cast<short>(MAX_AMP * amp);

        short result = static_cast<short>(amplitude * sin(rad));
        return result;
    }
```

In studying these things, I'm getting a good picture of just how far I have to go. Now I know that I need to gain a better understanding of the science of sound and how it is represented in a digital environment. Here's my first benchmark: I will build a simple synth that responds to key presses and generates a particular pitch for as long as the key is pressed.

- Remember `ncurses.h` library, that it can handle keyboard input (while key is pressed, etc.)
- Check if SFML can handle the same sort of input. It can!
- Explore SFML documentation carefully to get a grasp on the `<SFML/Window/Keyboard.hpp>` library and the `sound` class (make use of `sound.getStatus()` and `sf::Keyboard::isKeyPressed(A)`).
- Create 8 SoundBuffers and sample Vectors, 1 for each note in a diatonic scale.
- Create an array of the calculated frequencies given some fundamental - great place to use `constexpr`!

  ```
  constexpr double tonic = 220.0F; // Change this value to change the key signature

  constexpr double scale[8] = {
      tonic, tonic * (9.0/8), tonic * (5.0/4), tonic * (4.0/3),
      tonic * (3.0/2), tonic * (5.0/3), tonic * (15.0/8), tonic * 2
  };
  ```
- Simple program handles sine waves and square waves with polyphony! The computer fans get pretty loud while this program runs, so I'm pretty sure its very inefficient. Here's a [link](../files/sfmlPractice0/main.cpp).

The next step for this project is to improve the current while loop with the use of events. Furthermore, I'd like to start exploring the embedded side soon.

### 2/21/2023
Worked out some of the kinks in my implementation of TriangleWave and SawToothWave. I'm still a little unsure why they are quieter than the SineWave and SquareWave. Also, sometimes certain notes in the scale are louder than others; I haven't figured out why that is. I want to see if SFML will let me render a graph to display the waveform. That would really help me see what is going on with these functions:

```
short SawToothWave(int samplePart, double frequency, double amplitude) {
    int samplesPerCycle = static_cast<int>(SAMPLE_RATE / frequency);
    int halfCycle {samplesPerCycle / 2};
    // Treat each cycle as its own discrete set
    int cyclePart {samplePart % samplesPerCycle};
    short amp = static_cast<short>(MAX_AMP * amplitude);

    short result;
    if (cyclePart < halfCycle) {
        result = static_cast<short>(amp * (cyclePart / halfCycle));
    } else {
        result = static_cast<short>(amp * ((cyclePart - samplesPerCycle) / halfCycle));
    }
    return result;
}

short TriangleWave(int samplePart, double frequency, double amplitude) {
    int samplesPerCycle = static_cast<int>(SAMPLE_RATE / frequency);
    // Treat each cycle as its own discrete set
    int cyclePart {samplePart % samplesPerCycle};
    int halfCycle {samplesPerCycle / 2};
    short amp = static_cast<short>(MAX_AMP * amplitude);

    short result;
    if (cyclePart < halfCycle) {
        result = static_cast<short>(amp * (cyclePart / halfCycle));
    } else {
        result = static_cast<short>(amp * ((samplesPerCycle - cyclePart) / halfCycle));
    }
    return result;
}
```

