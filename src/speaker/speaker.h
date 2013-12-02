/*
 * spiker.h
 *
 *  Created on: 06-11-2013
 *      Author: embedded
 */

#ifndef SPIKER_H_
#define SPIKER_H_

#include "../sd/pff.h"
#include "../startup/printf_P.h"
#include "../startup/lpc2xxx.h"
#include "../timer/timer.h"
#include "../startup/general.h"

typedef struct { //główny nagłówek, określamy jaki układ bitów
	tU32 chunkId; //big
	tU32 chunkSize; //little
	tU32 format; //big
} WAVEHEADER;

typedef struct {
	tU32 subChunkId; //big [fmt ]
	tU32 subChunkSize; //little
	tU16 audioFormat; //little
	tU32 numChannels; //little
	tU32 sampleRate; //little
	tU32 byteRate; //little
	tU32 blockAlign; //little
	tU32 bitsPerSample; //little
} FmtChunk; //fmt


typedef struct {
	tU32 subChunkId; //big [data]
	tU32 subChunkSize; //little //data/samples size
	tU32 byteToOmmit; //where is the first sample
} DataChunk; //data

tBool initSpiker();
tBool play();
void playBuu();

#endif /* SPIKER_H_ */
