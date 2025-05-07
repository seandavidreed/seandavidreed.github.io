#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include "sound.h"

using namespace std;

constexpr double tonic = 220.0F; // Change this value to change the key signature

constexpr double scale[8] = {
    tonic, tonic * (9.0/8), tonic * (5.0/4), tonic * (4.0/3),
    tonic * (3.0/2), tonic * (5.0/3), tonic * (15.0/8), tonic * 2
};

int main() {

    // A C-style array where each element is equivalent to a C-style array
    sf::Int16 samples[8][44100];

    // Initialize samples
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 44100; j++) {
            samples[i][j] = sound::SquareWave(j, scale[i], 0.8);
        }
    }

    // 
    sf::SoundBuffer bufArray[8];
    sf::Sound tones[8];
    for (int i = 0; i < 8; i++) {
        bufArray[i].loadFromSamples(samples[i], sizeof(samples[i]) / sizeof(short), 1, 44100);
        tones[i].setBuffer(bufArray[i]);
        tones[i].setLoop(true);
    }

    while (1) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && tones[0].getStatus() != 2) tones[0].play();
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A)) tones[0].stop();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && tones[1].getStatus() != 2) tones[1].play();
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S)) tones[1].stop();
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && tones[2].getStatus() != 2) tones[2].play();
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D)) tones[2].stop();
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && tones[3].getStatus() != 2) tones[3].play();
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F)) tones[3].stop();
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && tones[4].getStatus() != 2) tones[4].play();
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::G)) tones[4].stop();
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && tones[5].getStatus() != 2) tones[5].play();
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::H)) tones[5].stop();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && tones[6].getStatus() != 2) tones[6].play();
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::J)) tones[6].stop();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && tones[7].getStatus() != 2) tones[7].play();
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::K)) tones[7].stop();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) break;
    }
    
    return 0;
}