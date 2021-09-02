#include "iostream"
#include <string>

using namespace std;

#include "SoundSamples.h"

class soundio
{
    public:
        static void OutputSound (SoundSamples * samples, string filename);
};