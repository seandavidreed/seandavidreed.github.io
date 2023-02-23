MODULES=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
CFLAGS=-std=c++20

all: simpleSynth

simpleSynth: main.o waveform.o
	$(CXX) $(CFLAGS) -o simpleSynth main.o waveform.o $(MODULES)

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

waveform.o: waveform.h waveform.cpp
	$(CXX) $(CFLAGS) -c waveform.cpp

clean:
	rm -f *o simpleSynth