#include "iostream"
#include <string>
#include <math.h> 

using namespace std;

#include "SoundSamples.h"

const float PI = 3.14;

/**
* Superclass that provides method generateFunction that must be redefined in subclasses. 
* Also has a unique name and a generateSamples method that outputs a SoundSamples array.
**/
class wave
{
    protected:
        string name;

    public:
        SoundSamples * generateSamples (float freqency, float sampleRate, float duration);

        virtual float generateFunction (float time) = 0;
};

/**
*Subclass of wave that generates basic sin wave.
**/
class SineWave : public wave
{
    public:
        SineWave (string _name)
        {
            this->name = _name;
        }

        float generateFunction (float time)
        {
            return sin (2 * PI * time);
        }
};

/**
*Subclass of wave that generates square sin wave.
**/
class SquareWave : public wave
{
    public:
        SquareWave (string _name)
        {
            this->name = _name;
        }

        float generateFunction (float time)
        {
            if (sin (2 * PI * time) >= 0) return 1.0;
            else return -1.0;
        }
};

/**
*Subclass of wave that generates triangular sin wave.
**/
class TriangleWave : public wave
{
    public:
        TriangleWave (string _name)
        {
            this->name = _name;
        }

        float generateFunction (float time)
        {
            return (2 / PI) * asin (sin (2 * PI * time));
        }
};

/**
*Subclass of wave that generates sawtooth sin wave.
**/
class SawtoothWave : public wave
{
    public:
        SawtoothWave (string _name)
        {
            this->name = _name;
        }

        float generateFunction (float time)
        {
            return -(2 / PI) * atan (1 / (tan (PI * time)));
        }
};