#include "wavfile.h"
#include<iostream>

// vr: la lib c s'inclut avec un c devant les noms de fichier d'entête et sans .h (comme lea lib c++ on ne met plus le .h genre #include<iostream> et pas #include <iostream.h>)
#include <cstdio>
#include <cstdlib>
#include <cstring>

// vr: le code des fichiers wavfile sont du c, vous l'avez récupéré sur Internet, ce qui ne me dérange pas puisque nous n'avons pas vu en cours les notions liées aux fichiers wav, par contre il est de bon ton de citer ses sources (même dans des projets et TPs internes aux mines),. La personne qui a mis ce code en accès libre a dû lui attribuer une licence particulière dont il faut tenir compte

struct wavfile_header {
	char	riff_tag[4];
	int	riff_length;
	char	wave_tag[4];
	char	fmt_tag[4];
	int	fmt_length;
	short	audio_format;
	short	num_channels;
	int	sample_rate;
	int	byte_rate;
	short	block_align;
	short	bits_per_sample;
	char	data_tag[4];
	int	data_length;
};

// vr: ouvre le fichier et y ećrit l'entête de RIFF...
FILE * wavfile_open( const char *filename )
{
  // vr: essayer d'ouvrir le fichier avant de calculer quoi que ce soit puisque vous arrêtez la fonction
  FILE * file = fopen(filename,"wb+");
	// vr: je remplace votre return 0 par un throw d'une erreur comme cela la fonction writting n'est pas continuée
	if(!file) throw("CANNOT OPEN FILE");

	struct wavfile_header header;

	int samples_per_second = WAVFILE_SAMPLES_PER_SECOND;
	int bits_per_sample = 16;

	strncpy(header.riff_tag,"RIFF",4);
	strncpy(header.wave_tag,"WAVE",4);
	strncpy(header.fmt_tag,"fmt ",4);
	strncpy(header.data_tag,"data",4);

	header.riff_length = 0;
	header.fmt_length = 16;
	header.audio_format = 1;
	header.num_channels = 1;
	header.sample_rate = samples_per_second;
	header.byte_rate = samples_per_second*(bits_per_sample/8);
	header.block_align = bits_per_sample/8;
	header.bits_per_sample = bits_per_sample;
	header.data_length = 0;

	fwrite(&header,sizeof(header),1,file);

	fflush(file);

	return file;

}

void wavfile_write( FILE *file, short data[], int length )
{
       fwrite(data,sizeof(short),length,file);
}

void wavfile_close( FILE *file )
{
	int file_length = ftell(file);

	int data_length = file_length - sizeof(struct wavfile_header);
	fseek(file,sizeof(struct wavfile_header) - sizeof(int),SEEK_SET);
	fwrite(&data_length,sizeof(data_length),1,file);

	int riff_length = file_length - 8;
	fseek(file,4,SEEK_SET);
	fwrite(&riff_length,sizeof(riff_length),1,file);

	fclose(file);
}
