#include <iostream>
#include <string>

#include "soundio.h"
#include "wave.h"

using namespace std;

/**
*This main method asks for the details that make a sound wave and outputs the samples from that wave to a file that is specified by the user.
*@return int indicating success
**/
int main () 
{
    string name;
    int typeWave;
    float sampleRate;
    float frequency;
    float duration;

    cout << "Type the number that corresponds to the wave you want (1=sine; 2=square; 3=triangle; 4=sawtooth):\n";
  
    cin >> typeWave;

    cout << "Type a sample rate:\n";

    cin >> sampleRate;

    cout << "Type a frequency:\n";

    cin >> frequency;

    cout << "Type a duration:\n";

    cin >> duration;

    cout << "Type a name for this wave:\n";

    cin >> name;

    wave *w;

    if (typeWave == 1)
    {
        w = new SineWave (name);
    }
    else if (typeWave == 2)
    {
        w = new SquareWave (name);
    }
    else if (typeWave == 3)
    {
        w = new TriangleWave (name);
    }
    else if (typeWave == 4)
    {
        w = new SawtoothWave (name);
    }
    else
    {
        cout << "Your wave number is invalid..";
        return 0;
    }

    SoundSamples * s = w->generateSamples (frequency, sampleRate, duration);

    soundio :: OutputSound (s, name);

    return 0;
}