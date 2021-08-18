#include "SoundSamples.h"

/**
*SoundSamples constructor that takes all important componants to create SoundSamples
*@param samples as a float array, length as an integer, and sample rate as a float
**/
SoundSamples :: SoundSamples (float *_samples, int _length, float _sampleRate)
{
  int i;
  //this->samples = _samples;
  int size = _length;
  float samps [size];
  for (i = 0; i < _length; i++) samps [i] = _samples [i];

  this->samples = samps;
  this->length = _length;
  this->sampleRate = _sampleRate;
}

/**
*SoundSamples constructor that takes all important componants to create empty SoundSamples (i.e. silence).
*@param length as an integer and sample rate as a float
**/
SoundSamples :: SoundSamples (int _length, float _sampleRate)
{
  int i;

  this->length = _length;
  this->sampleRate = _sampleRate;
  
  //create the silent samples:
  int size = _length;
  float samps [size];
  for (i = 0; i < size; i++) samples [i] = 0;
  this->samples = samps;
}

/**
*Overloaded operator that assigns one SoundSample to the left hand side SoundSample.
*@param SoundSamples pointer for a Sound Sample to be assigned 
*@return SoundSamples that has a new assignment
**/
SoundSamples& SoundSamples :: operator= (const SoundSamples &orig)
{
  if (this != &orig)
  {
    delete this->samples;

    this->length = orig.length;
    this->sampleRate = orig.sampleRate;

    this->samples = new float;
    *(this->samples) = *(orig.samples);
  }
  
  return *this;
}

/**
*Overloaded operator that checks to see if two SoundSamples are the same.
*@param SoundSample pointer to be compoared
*@return boolean indicator of whether two SoundSamples are the same
**/
bool SoundSamples :: operator== (const SoundSamples &s1/*, const SoundSamples &s2*/)
{
  int i;

  bool same = true;
  if (s1.length != this->length ) same = false;
  if (s1.sampleRate != this->sampleRate) same = false;
  for (i = 0; i < s1.length; i++)
    if (s1.samples [i] != this->samples [i]) same = false;

  return same;
}

/**
*Overloaded operator that adds one SoundSample to the left hand side SoundSample.
*@param SoundSamples for a Sound Sample to be added
*@return added SoundSample to the right of the operator, with the left added on
**/
SoundSamples SoundSamples :: operator+ (SoundSamples s1/*, const SoundSamples s2*/)
{
  int i;

  //SoundSamples add = s1;
  //add.length += s2.length;

  this->length += s1.length;

  std::cout << "idk";

  //const int size = add.length;
  int size = this->length;
  float samps [size];
  for (i = 0; i < size; i++)
  {
    //if (i < (size - s2.length)) samps [i] = s1.samples [i];
    if (i < (size - s1.length)) samps [i] = this->samples [i];
    else samps [i] = s1.samples [i - (size - s1.length)];
  }

  std::cout << "testp1";

  //add.samples = samps;
  delete this->samples;
  this->samples = samps;

  std::cout << "test";

  //return add;
  return *this;
}

/**
*Get method for the sample rate.
*@return float representing sample rate
**/
float SoundSamples :: getSampleRate ()
{
  return this->sampleRate;
}

/**
*Get method for the length of the sample array.
*@return float representing length of samples
**/
int SoundSamples :: getLength ()
{
  return this->length;
}

/**
*Override method for the sample at the specified index.
*@param index for desired sample
*@return float representing a single sound sample
**/
float & SoundSamples :: operator[] (int index)
{
  return samples [index];
}

void SoundSamples :: reverb2 (float delay, float attenuation)
{
  int i;

  if (delay < 0) 
  {
    std::cerr << "Error: delay value is less than zero\n";
    return;
  }
  if (attenuation < 0)
  {
    std::cerr << "Error: attenuation value is less than zero\n";
    return;
  }

  int sdelay = this->sampleRate * delay;

  int size = this->length;
  float samps [size];
  for (i = 0; i < size; i++)
  {
    //if (i < (size - s2.length)) samps [i] = s1.samples [i];
    if (i < sdelay) samps [i] = this->samples [i];
    else samps [i] = this->samples [i] + samps [i - sdelay] * attenuation;
  }

  this->samples = samps;
}

void SoundSamples :: asdr (float atime, float alevel, float dtime, float slevel, float rtime)
{
  int i;

  if (((atime * sampleRate) + (dtime * sampleRate) + (rtime * sampleRate)) > this->length) 
  {
    std::cerr << "Error: The three times given are greater then the duration of the sound sample currently defined\n";
    return;
  }

  //y - y1 = m (x - x1)

  //m1: 0 - alevel(y) = m (0 - atime(x)) -> m = y / x
  float m1 = alevel / atime;

  //m2: alevel - slevel(y) = m (atime - (atime + dtime)(x))
  float m2 = (alevel - slevel) / (atime - (atime + dtime));

  //m3: slevel - 0(y) = m ((totalDuration - rtime) - totalDuration(x))
  float m3 = alevel / (((this->length / this->sampleRate) - rtime) - (this->length / this->sampleRate));

  int size = this->length;
  float samps [size];
  for (i = 0; i < size; i++)
  {
    if (i < atime * sampleRate) samps [i] = this->samples [i] * m1;
    else if (i < (atime * sampleRate) + (dtime * sampleRate)) samps [i] = this->samples [i] * (alevel - m2 * (atime * sampleRate - i));
    else if (i < size - (rtime * sampleRate)) samps [i] = this->samples [i] * slevel;
    else samps [i] = this->samples [i] * (slevel - m3 * (((size * sampleRate) - (rtime * sampleRate)) - i));
  }

  this->samples = samps;
}