#include <iostream>
#include <fstream>
#include "soundio.h"

/**
*This method is what output all sound samples from the input into the specified file.
*@param samples in the type of SoundSamples and a filename of type string.
**/
void soundio :: OutputSound (SoundSamples * samples, string filename)
{
    int i;

    ofstream myFile;
    myFile.open (filename + ".txt");

    for (i = 0; i < samples->getLength (); i++)
    {
        myFile << (*samples) [i] << "\n";
        cout << (*samples) [i] << "\n";
    }
    myFile.close ();
}