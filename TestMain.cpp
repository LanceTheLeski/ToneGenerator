#include <iostream>
#include <string>
#include <math.h>

#include "soundio.h"
#include "wave.h"

using namespace std;

/**
*This main method asks for the details that make a sound wave and outputs the samples from that wave to a file that is specified by the user.
*@return int indicating success
**/
int main() 
{
    string name;
    int typeWave;

    float delay;
    float att;
    float atime;
    float alevel;
    float dtime;
    float slevel;
    float rtime;

    float sampleRate;
    float frequency;
    float duration;

    cout << "Type the number that corresponds to the wave you want (1=sine; 2=square; 3=triangle; 4=sawtooth):\n";
  
    cin >> typeWave;

    cout << "Type a delay:\n";

    cin >> delay;

    cout << "Type a attenuation:\n";

    cin >> att;

    cout << "Type the attack time (atime):\n";

    cin >> atime;

    cout << "Type the attack level (alevel):\n";

    cin >> alevel;

    cout << "Type the decay time (dtime):\n";

    cin >> dtime;

    cout << "Type the sustaine level (slevel):\n";

    cin >> slevel;

    cout << "Type the release time (rtime):\n";

    cin >> rtime;

    cout << "Type a name for the output file:\n";

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
        cerr << "Your wave number is invalid..\n";
        return 0;
    }

    //get keys and calculate SoundSamples

    //SoundSamples * s = NULL;
    SoundSamples pause = SoundSamples (.25 * sampleRate, sampleRate);
    sampleRate = 44100;
    duration = 1;

    int key;

    cout << "Type set of keys:\n";

    cin >> key;

    while (key >= 0)
    {
        frequency = 440 * pow (2, ((key - 49)/12));

        SoundSamples * n = w->generateSamples (frequency, sampleRate, duration);
        n->reverb2 (delay, att);

        soundio :: OutputSound (n, name);
        soundio :: OutputSound (&pause, name);

        cin >> key;
    }

    return 0;
}