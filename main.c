#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <portaudio.h>
#include <sndfile.h>

#define CHUNK 2048
#define SAMPLE_RATE 44100


static int paRecordCallback(const void* inputBuffer, void* outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData)
{
    SNDFILE* file = (SNDFILE*)userData;
    float* in = (float*)inputBuffer;

    sf_writef_float(file, in, framesPerBuffer);
    return 0;
}

int main() {
    PaError err = paNoError;
    SF_INFO info = { .channels = 1, .format = SF_FORMAT_WAV|SF_FORMAT_FLOAT, .frames = CHUNK,.samplerate = SAMPLE_RATE };
    SNDFILE* file = sf_open("test.wav", SFM_WRITE, &info);
    if ((err = Pa_Initialize()) != paNoError) goto error;

    PaStream* stream;

    err = Pa_OpenDefaultStream(&stream, 1, 0, paFloat32, SAMPLE_RATE, CHUNK, paRecordCallback, file);
    if (err != paNoError) goto error;

    err = Pa_StartStream(stream);
    if (err != paNoError) goto error;

    Pa_Sleep(1000 * 5);

    err = Pa_StopStream(stream);
    if (err != paNoError) goto error;

    Pa_Terminate();
    sf_close(file);
    puts("done!");
    return 0;

error:
    Pa_Terminate();
    sf_close(file);
    puts(Pa_GetErrorText(err));
    return 1;
}