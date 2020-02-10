#pragma once
#include "AudioSource.h"
class AudioListener
{
private:
	void setListenerPosition(float x, float y, float z);
	void setListenerVelocity(float x, float y, float z);
    void setListenerOrientation(float x, float y, float z);
public:
    static AudioListener& getInstance()
    {
        static AudioListener    instance;
        instance.setListenerPosition(0, 0, 0);
        instance.setListenerVelocity(0, 0, 0);
        instance.setListenerOrientation(0, 0, 0);
        return instance;
    }
public:
    AudioListener() {}                   

//public:
//    AudioListener(AudioListener const&) = delete;
//    void operator=(AudioListener const&) = delete;

};