#include "wave.h"

#include <iostream>

/**
*This method takes a frequency, sampleRate, and duration and converts them to a SoundSamples.
*@param frequency is a float, sampleRate is a float indicating the rate of samples, duration is a float that indicates the length of time the sound should be played over.
*@return SoundSamples with complete list of samples
**/
SoundSamples * wave :: generateSamples (float frequency, float sampleRate, float duration)
{
    int time;

    int size = sampleRate * duration;
    float samples [size];

    for (time = 0; time < (sampleRate * duration); time ++)
    {
        samples [time] = generateFunction (((frequency * time) / sampleRate));
        //sin (((2 * PI) * frequency * time) / sampleRate);
    }

    SoundSamples *result = new SoundSamples (samples, size, sampleRate);

    return result;
}