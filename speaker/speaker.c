#include "speaker.h"

static tU8 wave_stream_buf[512 * 1];//1 sectors

WORD bytesReaded;
FRESULT rc;

WAVEHEADER wh;
FmtChunk ws1;
DataChunk ws2;
FATFS fatfs; /* File system object */
FRESULT rcv;

tBool initSpiker(void) {
	bytesReaded = 0;

	tU32 i = 0;

	//	printf("read data\n");
	rc = pf_read(wave_stream_buf, sizeof(wave_stream_buf), &bytesReaded);

	if (rc || !bytesReaded)
		return FALSE;

	//	printf("fill structs\n");
	//wave header
	wh.chunkId = wave_stream_buf[i++] << 24;
	wh.chunkId += wave_stream_buf[i++] << 16;
	wh.chunkId += wave_stream_buf[i++] << 8;
	wh.chunkId += wave_stream_buf[i++];

	wh.chunkSize = wave_stream_buf[i++];
	wh.chunkSize += wave_stream_buf[i++] << 8;
	wh.chunkSize += wave_stream_buf[i++] << 16;
	wh.chunkSize += wave_stream_buf[i++] << 24;

	wh.format = wave_stream_buf[i++] << 24;
	wh.format += wave_stream_buf[i++] << 16;
	wh.format += wave_stream_buf[i++] << 8;
	wh.format += wave_stream_buf[i++];

	ws1.subChunkId = wave_stream_buf[i++] << 24;
	ws1.subChunkId += wave_stream_buf[i++] << 16;
	ws1.subChunkId += wave_stream_buf[i++] << 8;
	ws1.subChunkId += wave_stream_buf[i++];

	ws1.subChunkSize = wave_stream_buf[i++];
	ws1.subChunkSize += wave_stream_buf[i++] << 8;
	ws1.subChunkSize += wave_stream_buf[i++] << 16;
	ws1.subChunkSize += wave_stream_buf[i++] << 24;

	ws1.audioFormat = wave_stream_buf[i++];
	ws1.audioFormat += wave_stream_buf[i++] << 8;

	ws1.numChannels = wave_stream_buf[i++];
	ws1.numChannels += wave_stream_buf[i++] << 8;

	ws1.sampleRate = wave_stream_buf[i++];
	ws1.sampleRate += wave_stream_buf[i++] << 8;
	ws1.sampleRate += wave_stream_buf[i++] << 16;
	ws1.sampleRate += wave_stream_buf[i++] << 24;

	ws1.byteRate = wave_stream_buf[i++];
	ws1.byteRate += wave_stream_buf[i++] << 8;
	ws1.byteRate += wave_stream_buf[i++] << 16;
	ws1.byteRate += wave_stream_buf[i++] << 24;

	ws1.blockAlign = wave_stream_buf[i++];
	ws1.blockAlign += wave_stream_buf[i++] << 8;

	ws1.bitsPerSample = wave_stream_buf[i++];
	ws1.bitsPerSample += wave_stream_buf[i++] << 8;


	ws2.subChunkId = wave_stream_buf[i++] << 24;
	ws2.subChunkId += wave_stream_buf[i++] << 16;
	ws2.subChunkId += wave_stream_buf[i++] << 8;
	ws2.subChunkId += wave_stream_buf[i++];

	ws2.subChunkSize = wave_stream_buf[i++];
	ws2.subChunkSize += wave_stream_buf[i++] << 8;
	ws2.subChunkSize += wave_stream_buf[i++] << 16;
	ws2.subChunkSize += wave_stream_buf[i++] << 24;

	ws2.byteToOmmit = i;

	return TRUE;
}

#define BUFFSIZE 512 * 5 //wielkość bufora
#define BUFFCOUNT 2 //ilość buforów
tU8 buffer[BUFFCOUNT][BUFFSIZE]; //bufor na próbki

tU8 bufferPlayed = 0; //numer bufora z którego są aktualnie odczytywane dane
tU8 bufferToDownload = 0; //numer bufora który należy uzupełnić
tU16 sample = 0; //dana próbka z bufora
unsigned long long totalPlayed = 0; //ilość oftworzonych próbek
tBool refil = FALSE; //czy bufor pusty

tBool play() {
	bufferPlayed = 0;
	bufferToDownload = 0;
	sample = 0;
	totalPlayed = 0;
	refil = FALSE;

	bytesReaded = 0;

	tU32 i = 0;
	pf_lseek(ws2.byteToOmmit);

	//wypełniamy na sam początek czymś
	do {
		rc = pf_read(buffer[i], sizeof(buffer[i]), &bytesReaded);
		i++;
	} while (i < BUFFCOUNT && !rc && bytesReaded);

	tU32 uplynelo = 0;
	tU32 czasCalkowity = ws2.subChunkSize / ws1.byteRate;
	//ilość próbek przez prędkosć odtwarzania
	tU32 pozostalo = 0;

	while (totalPlayed < ws2.subChunkSize) {
		if (sample >= (BUFFSIZE)) {
			sample = 0;
			bufferToDownload = bufferPlayed++;
			refil = TRUE;
		}
		if (bufferPlayed >= BUFFCOUNT)
			bufferPlayed = 0;

		if (ws1.bitsPerSample == 8)
			DACR = buffer[bufferPlayed][sample++] << 5;
		else if (ws1.bitsPerSample == 16)
			DACR = ((buffer[bufferPlayed][sample++] << 8)
					+ (buffer[bufferPlayed][sample++])) << 5;

		if (refil) { //uzupełnij bufor nawet jak zapauzowane
			rc = pf_read(buffer[bufferToDownload],
					sizeof(buffer[bufferToDownload]), &bytesReaded);
			refil = FALSE;
		} else if (refil == FALSE) {
			if (totalPlayed % ws1.byteRate != 0)
				sleep(1000000 / (ws1.byteRate + 2500));
			//trzeba przyśpieszyć mimo wszystko o jakieś 2500 próbek
			//ekran bowiem daje za duże opóźnienia :/ i tak to nie jest
			//doskonałe
			//gdy odczyt z karty, to on służy za opóxnienie, więc nie czekaj

		}
		totalPlayed++;
	}
	return TRUE;
}

void playBuu() {
	rcv = pf_mount(&fatfs);
	rcv = pf_open("buu.wav");
	if (rcv == FR_OK) {
		if (initSpiker()) { //inicjacja nagłówków wave{
			if (play()) {

			}
		}
	}
	rcv = pf_mount(0);
}
