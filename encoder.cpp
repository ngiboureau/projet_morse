#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include "wavfile.h"

// vr: vous auriez dû faire une classe avec en attribut le dictionnaire morse et en méthodes les fonctions de conversion

// vr: passez l'argument par référence pour en pas le recopier et const pour ne pas le modifier 
// vr: votre code manque de commentaires
std::string convert(const std::string& mess)
{
// vr: à chaque fois que vous appelez cette fonction vous construisez ces deux listes ce qui est très cher en mouvements mémoire inutiles et en temps, et votre code ne peut donc pas être utilisé dans un système qui proposerait de traduire plusieurs phrases   

// vr: vous devez utilsier un dictionnaire, le temps de recherche d'un élément par key sera constant contre linéaire dans votre cas
  const char letters[37] = { ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

  //vr: pourquoi des espaces entre les symboles du morse et pourquoi _ qui est difficile à voir
  // vr:const std::string morseLetters[37] = { " ", ". _", "_ . . .", "_ . _ .", "_ . .", ".", ". . _ .", "_ _ .", ". . . .", ". .", ". _ _ _", "_ . _", ". _ . .",  "_ _", "_ .", "_ _ _", ". _ _ .", "_ _ . _", ". _ .", ". . .", "_", ". . _", ". . . _", ". _ _", "_ . . _", "_ . _ _", "_ _ . .", ". _ _ _ _", ". . _ _ _", ". . . _ _", ". . . . _", ". . . . .", "_ . . . .", "_ _ . . .", "_ _ _ . .", "_ _ _ _ .", "_ _ _ _ _"};
    const std::string morseLetters[37] = { " ", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..",  "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"};
    // vr: je garde le nb de lettres pour vérifiez qu'on ne sort pas du votre tableau lors de la ercherche
    const int nb_letters = 37;
    
    std::string morseMess = "";
    // vr: vous avez deux boucles sur le même i ? pour parcourir une string ?
    // vr:    for (int i = 0; i < mess.length(); i++)
    // vr: ne pas recalculer la longueur de la chaine à chaque itération
    size_t mess_length = mess.length();
    for (size_t i = 0; i < mess_length; i++)
      {
	// vr: si i est un size_t restez cohérent et mettez j aussi size_t
	size_t j = 0;
	
	// vr: voila où vous faites une rechercher linéaire contre une recherche en temps constant si vous prenez une std::map
	while ( (j != nb_letters) and (letters[j] != mess[i]) ) {
	  // vr: si la lettre n'est pas trouvée il faut arrêter la boucle
	  j++;
	}
	if (j == nb_letters) 
	  // vr: attention à la segfault en accédant à morseLetters[j] si j est égal à nb_letters, préférez lancer une exception pour permettre à l'utilisateur de votre code de rattraper son erreur (je le fais dans le main)
	  
	  throw ("NOT A LETTER");
	morseMess.append(morseLetters[j]);
	// vr: morseMess.append(morseLetters[0]);
	// vr: morseMess.append(morseLetters[0]);
	// vr: ne mettez pas 3 espaces après chaque lettre morse, un seul suffit et 2 espaces entre les mots (par exemple) donc lorsque la lettre est un espace on ne rajoute pas le 3ième espace
	if (mess[i] != ' ')
	  morseMess.append(morseLetters[0]);
      }
    return morseMess;
}

float SHORT = 0.1;
float LONG = 0.4;

// vr: j'ai besoin d'un silence pour séparer les signes (. et -) dans le fichier de son wav
void writingShortSilence(FILE * f)
{
  const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*SHORT);
  short waveform[NUM_SAMPLES];
    // vr: double frequency = 440.0; variable non utilisée ?
    // vr: idem int volume = 32000; 
	int length = NUM_SAMPLES;

	// vr: int i;
	for(int i=0;i<length;i++) {
		waveform[i] = 0;
	}
    
	wavfile_write(f,waveform,length);
}

void writingShortSound(FILE * f)
{
  // vr: 0.1 doit être un attribut quelque part (je le mets ci-dessus)
    const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*SHORT);
    short waveform[NUM_SAMPLES];
    // vr: ces attirbuts devraient être rangés dans une class
	double frequency = 440.0;
	int volume = 32000;
	int length = NUM_SAMPLES;

	// vr:mettez la définition du i dans la boucle // int i;
	for(int i=0;i<length;i++) {
		double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
		waveform[i] = volume*sin(frequency*t*2*M_PI);
	}
    
	wavfile_write(f,waveform,length);
	// vr: on doit séparer les signes par un petit silence
	writingShortSilence(f);
}

void writingLongSound(FILE * f)
{
  // vr: 0.3 doit être un attribut quelque part
    const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*LONG);
    short waveform[NUM_SAMPLES];
	double frequency = 440.0;
	int volume = 32000;
	int length = NUM_SAMPLES;

	for(int i=0;i<length;i++) {
		double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
		waveform[i] = volume*sin(frequency*t*2*M_PI);
	}
    
	wavfile_write(f,waveform,length);
	// vr: on doit séparer chaque lettre par un silence
	writingShortSilence(f);
}

void writingSilence(FILE * f)
{
  const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*LONG);
  short waveform[NUM_SAMPLES];
    // vr: double frequency = 440.0; variable non utilisée ?
    // vr: idem int volume = 32000; 
	int length = NUM_SAMPLES;

	// vr: int i;
	for(int i=0;i<length;i++) {
		waveform[i] = 0;
	}
    
	wavfile_write(f,waveform,length);
}

void writing(const std::string& messMorse)
{
    FILE * f = wavfile_open("morse.wav");
    for (int i = 0; i < messMorse.length(); i++)
    {
        switch(messMorse[i]) {
        case '.':
            writingShortSound(f);
            break;
	    // vr: j'ai mis - à la place de _
        case '-':
            writingLongSound(f);
            break;
	case ' ':
	    writingSilence(f);
	    break;
        }    
    }
    wavfile_close(f);
}
