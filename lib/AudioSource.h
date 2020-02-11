#pragma once
#include "AudioBuffer.h"

class AudioSource
{
	ALuint m_iSource;
public:
	AudioSource(AudioBuffer* buffer);
	void getPitch(float* _value);
	void getPosition(float* _x, float* _y, float* _z);
	void setPitch(float pitch);
	void setGain(float gain);
	void setLooping(bool loop);
	void increasePitch();
	void decreasePitch();
	void setBuffer(AudioBuffer* buffer);
	void setPosition(float x, float y, float z);
	void setVelocity(float x, float y, float z);
	void moveRight();
	void moveLeft();
	void play();
	void stop();
	void pause();
	bool isPlaying() const;
};
