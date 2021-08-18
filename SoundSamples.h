#include "iostream"
#pragma once

class SoundSamples
{
  private:
    float sampleRate;
    float *samples;
    int length;

  public:
    SoundSamples ()
    {
      sampleRate = 8000;
      //No samples
      length = 0;
    }

    SoundSamples (float * _samples, int _length, float _sampleRate);

    SoundSamples (int _length, float _sampleRate);

    float getSampleRate ();

    int getLength ();

    float & operator[] (int index);

    SoundSamples & operator= (const SoundSamples &orig);

    bool operator== (const SoundSamples &s1/*, const SoundSamples &s2*/);

    SoundSamples operator+ (SoundSamples s1/*, SoundSamples s2*/);

    void reverb2 (float delay, float attenuation);

    void asdr (float atime, float alevel, float dtime, float slevel, float rtime);
};