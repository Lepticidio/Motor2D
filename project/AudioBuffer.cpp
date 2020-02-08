#include "AudioBuffer.h"

AudioBuffer::AudioBuffer(uint32_t _iBuffer, ALvoid* _data)
	: m_iBuffer(_iBuffer), m_data(_data)
{

}
AudioBuffer* AudioBuffer::load(const char* filename)
{
	FILE* pFile(nullptr);
	fopen_s(&pFile, filename, "r");
	fseek(pFile, 0, SEEK_END);
	const unsigned int uFileSize = (unsigned int)ftell(pFile);
	fclose(pFile);
	fopen_s(&pFile, filename, "r");
	if (pFile != nullptr)
	{
		unsigned char* sBuffer = new unsigned char[uFileSize];
		ALuint* pBuffer = nullptr;
		alGenBuffers(1, pBuffer);
		int readResult = fread(sBuffer, sizeof(unsigned char), uFileSize, pFile);
		int iChannels = (int)sBuffer[21];
		int iSampleRate = (int)(sBuffer[23] << 24 | sBuffer[24] << 16 | sBuffer[25] << 8 | sBuffer[26]);
		int iBitsPerSample = (int)sBuffer[33];
		ALenum format;
		ALvoid* pData = nullptr;
		if (iChannels == 1)
		{
			if (iBitsPerSample == 8)
			{
				format = AL_FORMAT_MONO8;
			}

			else if (iBitsPerSample == 16)
			{
				format = AL_FORMAT_MONO16;
			}
		}
		else
		{
			if (iBitsPerSample == 8)
			{
				format = AL_FORMAT_STEREO8;
			}

			else if (iBitsPerSample == 16)
			{
				format = AL_FORMAT_STEREO16;
			}
		}
		int iDataSize = 0;
		for (int i = 0; i < (int)uFileSize; i++)
		{
			if (sBuffer[i] == 'd')
			{
				if (sBuffer[i+1] == 'a')
				{
					if (sBuffer[i+2] == 't')
					{
						if (sBuffer[i+3] == 'a')
						{
							iDataSize = (int)(sBuffer[i + 4 + 0] << 24 | sBuffer[i + 4 + 1] << 16 | sBuffer[i + 4 + 2] << 8 | sBuffer[i + 4 + 3]);
							iDataSize = (int)(sBuffer[0] << 24 | sBuffer[1] << 16 | sBuffer[2] << 8 | sBuffer[3]);
						}
					}
				}
			}
		}

		alBufferData
		(
			*pBuffer,
			format,
			pData,
			iDataSize,
			iSampleRate
		);
		return new AudioBuffer(*pBuffer, pData);
	}
	else
	{
		return nullptr;
	}
}
uint32_t  AudioBuffer::getAlBuffer() const
{
	return m_iBuffer;
}