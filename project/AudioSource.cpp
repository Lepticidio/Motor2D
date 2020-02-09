#include "AudioSource.h"

AudioSource::AudioSource(AudioBuffer* buffer)
{
	ALuint* pID = new ALuint;
	alGenSources(1, pID);
	m_iSource = *pID;
	ALuint uBufferID = buffer->getAlBuffer();
	alSourcei(m_iSource, AL_BUFFER, uBufferID);
	alSourcei(m_iSource, AL_LOOPING, (int)false);
	alSourcef(m_iSource, AL_PITCH, 1);
	alSourcef(m_iSource, AL_GAIN, 1);
	alSource3f(m_iSource, AL_VELOCITY, 0, 0, 0);
}

void AudioSource::setPitch(float pitch)
{
	alSourcef(m_iSource, AL_PITCH, pitch);
}
void AudioSource::setGain(float gain)
{
	alSourcef(m_iSource, AL_GAIN, gain);
}
void AudioSource::setLooping(bool loop)
{
	alSourcei(m_iSource, AL_LOOPING, (int)loop);
}
void AudioSource::setBuffer(AudioBuffer* buffer)
{
	ALuint uBufferID = buffer->getAlBuffer();
	alSourcei(m_iSource, AL_LOOPING, uBufferID);
}
void AudioSource::setPosition(float x, float y, float z)
{
	alSource3f(m_iSource, AL_POSITION, x, y, z);
}
void AudioSource::setVelocity(float x, float y, float z)
{
	alSource3f(m_iSource, AL_VELOCITY, x, y, z);
}
void AudioSource::play()
{
	alSourcePlay(m_iSource);
}
void AudioSource::stop()
{
	alSourceStop(m_iSource);
}
void AudioSource::pause()
{
	alSourcePause(m_iSource);
}
bool AudioSource::isPlaying() const
{
	ALint* iResult = new ALint;
	alGetSourcei(m_iSource, AL_SOURCE_STATE, iResult);
	if (iResult != nullptr)
	{
		if (*iResult == AL_PLAYING)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}