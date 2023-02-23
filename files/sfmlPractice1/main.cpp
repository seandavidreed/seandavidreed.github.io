#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "waveform.h"

// Can be modified freely
constexpr double tonic = 220.0F;

/*  
 * Major scale tempered with Just Intonation
 * !! CAREFUL EDITING THIS ONE !! 
*/
constexpr double scale[8] = {
    tonic, 
    tonic * (9.0/8), 
    tonic * (5.0/4), 
    tonic * (4.0/3),
    tonic * (3.0/2), 
    tonic * (5.0/3), 
    tonic * (15.0/8), 
    tonic * 2
};

int main() {

    // Select the waveform with which to generate samples
    std::cout << "Choose a Waveform: " << std::endl;
    std::cout << "[1] Sine\n[2] Square\n[3] Triangle\n[4] Sawtooth" << std::endl;
    unsigned short choice;
    std::cin >> choice;


    // Assign function pointer according to selection
    short (*funcPtr)(int, double, double);
    switch (choice) {
        case 1:
            funcPtr = wf::SineWave;
        break;
        case 2:
            funcPtr = wf::SquareWave;
        break;
        case 3:
            funcPtr = wf::TriangleWave;
        break;
        case 4:
            funcPtr = wf::SawToothWave;
        break;
        default:
            std::cout << "Invalid choice. Exiting..." << std::endl;
            exit(-1);
    }


    // Declare samples array to be used for sample values
    // Declare sampleCoords array to be used for rendering waveform graphs
    sf::Int16 samples[8][static_cast<int>(wf::SAMPLE_RATE)];
    sf::VertexArray sampleCoords[8];
    
    // Initialize arrays
    for (int i = 0; i < 8; i++) {
        sampleCoords[i].resize(wf::SAMPLE_RATE);
        sampleCoords[i].setPrimitiveType(sf::LineStrip);
        for (int samplePart = 0; samplePart < wf::SAMPLE_RATE; samplePart++) {
            samples[i][samplePart] = funcPtr(samplePart, scale[i], 0.8);
            sampleCoords[i][samplePart].position = sf::Vector2f(samplePart, (samples[i][samplePart] / 400) + 400);
        }
    }


    // Load samples into buffer array then into tones array
    sf::SoundBuffer bufArray[8];
    sf::Sound tones[8];
    for (int i = 0; i < 8; i++) {
        bufArray[i].loadFromSamples(samples[i], sizeof(samples[i]) / sizeof(short), 1, 44100);
        tones[i].setBuffer(bufArray[i]);
        tones[i].setLoop(true);
    }


    // Open a window & Describe an x-axis
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Draw Waves");
    sf::VertexArray xAxis(sf::LineStrip, 1000);
    for (int i = 0; i < 1000; i++) {
        xAxis[i] = sf::Vertex(sf::Vector2f(i, 400), sf::Color::Red, sf::Vector2f(0, 10));
    }


    /*
     * Main Program Loop:
     * Detects a key press and release,
     * playing/stopping the corresponding
     * tone from the tones array.
    */ 
    while (window.isOpen()) {
        window.draw(xAxis);
        window.display();
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            tones[0].stop();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && tones[0].getStatus() != 2) {
            tones[0].play();
            window.clear();
            window.draw(sampleCoords[0]);
            window.display();
        }

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            tones[1].stop();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && tones[1].getStatus() != 2) {
            tones[1].play();
            window.clear();
            window.draw(sampleCoords[1]);
            window.display();
        }

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            tones[2].stop();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && tones[2].getStatus() != 2) {
            tones[2].play();
            window.clear();
            window.draw(sampleCoords[2]);
            window.display();
        } 
        
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            tones[3].stop();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && tones[3].getStatus() != 2) {
            tones[3].play();
            window.clear();
            window.draw(sampleCoords[3]);
            window.display();
        }
        
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
            tones[4].stop();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && tones[4].getStatus() != 2) {
            tones[4].play();
            window.clear();
            window.draw(sampleCoords[4]);
            window.display();
        }
        
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
            tones[5].stop();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && tones[5].getStatus() != 2) {
            tones[5].play();
            window.clear();
            window.draw(sampleCoords[5]);
            window.display();
        }

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
            tones[6].stop();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && tones[6].getStatus() != 2) {
            tones[6].play();
            window.clear();
            window.draw(sampleCoords[6]);
            window.display();
        }

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
            tones[7].stop();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && tones[7].getStatus() != 2) {
            tones[7].play();
            window.clear();
            window.draw(sampleCoords[7]);
            window.display();
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
    
    return 0;
}