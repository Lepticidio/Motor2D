#include "AudioListener.h"

void AudioListener::setListenerPosition(float x, float y, float z)
{
	alListener3f(AL_POSITION, x, y, z);
}
void AudioListener::setListenerVelocity(float x, float y, float z)
{
	alListener3f(AL_VELOCITY, x, y, z);
}
void AudioListener::setListenerOrientation(float x, float y, float z)
{
	alListener3f(AL_ORIENTATION, x, y, z);
}