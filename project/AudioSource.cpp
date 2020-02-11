#include "AudioSource.h"

AudioSource::AudioSource(AudioBuffer* buffer)
{
	ALenum auxError = alGetError();
	if (auxError != AL_NO_ERROR)
	{

		return;
	}
	ALuint* pID = new ALuint;
	alGenSources(1, pID);

	auxError = alGetError();
	if (auxError != AL_NO_ERROR)
	{

		return;
	}


	m_iSource = *pID;
	ALuint uBufferID = buffer->getAlBuffer();

	auxError = alGetError();
	if (auxError != AL_NO_ERROR)
	{

		return;
	}


	alSourcei(m_iSource, AL_BUFFER, uBufferID);
	alSourcei(m_iSource, AL_LOOPING, (int)false);
	alSourcef(m_iSource, AL_PITCH, 1);
	alSourcef(m_iSource, AL_GAIN, 1);
	alSource3f(m_iSource, AL_VELOCITY, 0, 0, 0);

	auxError = alGetError();
	if (auxError != AL_NO_ERROR)
	{

		return;
	}
}

void AudioSource::getPitch(float* _value)
{
	alGetSourcef(m_iSource, AL_PITCH, _value);
}

void AudioSource::getPosition(float* _x, float* _y, float* _z)
{
	alGetSource3f(m_iSource, AL_POSITION, _x, _y, _z);
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
void AudioSource::increasePitch()
{
	float* pValue = new float();
	getPitch(pValue);
	if (*pValue <= 2 - 0.001f)
	{
		setPitch(*pValue + 0.001f);
	}
}
void AudioSource::decreasePitch()
{
	float* pValue = new float();
	getPitch(pValue);
	if (*pValue >= 0.001f)
	{
		setPitch(*pValue - 0.001f);
	}
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

void AudioSource::moveRight()
{
	float* pX = new float();
	float* pY = new float();
	float* pZ = new float();
	getPosition(pX, pY, pZ);
	if (*pX <= 500.f)
	{
		setPosition(*pX + 0.00001f, *pY, *pZ);
	}
}

void AudioSource::moveLeft()
{
	float* pX = new float();
	float* pY = new float();
	float* pZ = new float();
	getPosition(pX, pY, pZ);
	if (*pX >= -500)
	{
		setPosition(*pX - 0.00001f, *pY, *pZ);
	}
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