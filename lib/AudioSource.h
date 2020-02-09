#pragma once
#include "AudioBuffer.h"

class AudioSource
{
	ALuint m_iSource;
public:
	AudioSource(AudioBuffer* buffer);
	void setPitch(float pitch);
	void setGain(float gain);
	void setLooping(bool loop);
	void setBuffer(AudioBuffer* buffer);
	void setPosition(float x, float y, float z);
	void setVelocity(float x, float y, float z);
	void play();
	void stop();
	void pause();
	bool isPlaying() const;
};
