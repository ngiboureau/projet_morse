#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include "wavfile.h"

std::string convert(std::string mess)
{
    const char letters[37] = { ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    const std::string morseLetters[37] = { " ", ". _", "_ . . .", "_ . _ .", "_ . .", ".", ". . _ .", "_ _ .", ". . . .", ". .", ". _ _ _", "_ . _", ". _ . .",  "_ _", "_ .", "_ _ _", ". _ _ .", "_ _ . _", ". _ .", ". . .", "_", ". . _", ". . . _", ". _ _", "_ . . _", "_ . _ _", "_ _ . .", ". _ _ _ _", ". . _ _ _", ". . . _ _", ". . . . _", ". . . . .", "_ . . . .", "_ _ . . .", "_ _ _ . .", "_ _ _ _ .", "_ _ _ _ _"};
    std::string morseMess = "";
    for (int i = 0; i < mess.length(); i++)
    {
        int j = 0;
        while (letters[j] != mess[i])
            j++;
        morseMess.append(morseLetters[j]);
        morseMess.append(morseLetters[0]);
        morseMess.append(morseLetters[0]);
        morseMess.append(morseLetters[0]);
    }
    return morseMess;
}

void writingShortSound(FILE * f)
{
    const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*0.1);
    short waveform[NUM_SAMPLES];
	double frequency = 440.0;
	int volume = 32000;
	int length = NUM_SAMPLES;

	int i;
	for(i=0;i<length;i++) {
		double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
		waveform[i] = volume*sin(frequency*t*2*M_PI);
	}
    
	wavfile_write(f,waveform,length);
}

void writingLongSound(FILE * f)
{
    const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*0.3);
    short waveform[NUM_SAMPLES];
	double frequency = 440.0;
	int volume = 32000;
	int length = NUM_SAMPLES;

	int i;
	for(i=0;i<length;i++) {
		double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
		waveform[i] = volume*sin(frequency*t*2*M_PI);
	}
    
	wavfile_write(f,waveform,length);
}

void writingVoid(FILE * f)
{
    const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*0.1);
    short waveform[NUM_SAMPLES];
	double frequency = 440.0;
	int volume = 32000;
	int length = NUM_SAMPLES;

	int i;
	for(i=0;i<length;i++) {
		waveform[i] = 0;
	}
    
	wavfile_write(f,waveform,length);
}

void writing(std::string messMorse)
{
    FILE * f = wavfile_open("morse.wav");
    for (int i = 0; i < messMorse.length(); i++)
    {
        switch(messMorse[i]) {
        case '.':
            writingShortSound(f);
            break;
        case '_':
            writingLongSound(f);
            break;
        default :
            writingVoid(f);
        }    
    }
    wavfile_close(f);
}