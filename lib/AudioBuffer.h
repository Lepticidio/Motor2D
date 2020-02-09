#pragma once
#include "../openal/AL/al.h"
#include "../openal/AL/alc.h"
#include <iostream>
class AudioBuffer
{
	ALvoid* m_data;
	uint32_t m_uBuffer;
	AudioBuffer(uint32_t _iBuffer, ALvoid* _data);
	static AudioBuffer* load(const char* filename);
public:
	uint32_t getAlBuffer() const;
};

