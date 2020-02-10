#include "AudioBuffer.h"

AudioBuffer::AudioBuffer(uint32_t _iBuffer, ALvoid* _data)
	: m_uBuffer(_iBuffer), m_data(_data)
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
		ALuint* pBuffer = new ALuint();
		alGenBuffers(1, pBuffer);


		ALenum auxError = alGetError();
		if (auxError != AL_NO_ERROR)
		{

			return 0;
		}

		int readResult = fread(sBuffer, sizeof(unsigned char), uFileSize, pFile);
		int iChannels = (int)(sBuffer[23] << 8 | sBuffer[22]);
		int iSampleRate = (int)(sBuffer[27] << 24 | sBuffer[26] << 16 | sBuffer[25] << 8 | sBuffer[24]);
		int iBitsPerSample = (int)(sBuffer[35] << 8 | sBuffer[34]);
		ALenum* pFormat = new ALenum ();
		if (iChannels == 1)
		{
			if (iBitsPerSample == 8)
			{
				*pFormat = AL_FORMAT_MONO8;
			}

			else if (iBitsPerSample == 16)
			{
				*pFormat = AL_FORMAT_MONO16;
			}
		}
		else
		{
			if (iBitsPerSample == 8)
			{
				*pFormat = AL_FORMAT_STEREO8;
			}

			else if (iBitsPerSample == 16)
			{
				*pFormat = AL_FORMAT_STEREO16;
			}
		}
		int iDataSize = 0;
		int iDataEndPosition = 0;
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
							iDataSize = (int)(sBuffer[i + 7] << 24 | sBuffer[i + 6] << 16 | sBuffer[i + 5] << 8 | sBuffer[i + 4]);
							iDataEndPosition = i + 8;
							break;
						}
					}
				}
			}
		}

		auxError = alGetError();
		if (auxError != AL_NO_ERROR)
		{

			return 0;
		}

		unsigned char* sData = new unsigned char [iDataSize];
		
		for (int i = 0; i < iDataSize; i++)
		{
			sData[i] = sBuffer[i + iDataEndPosition];
		}
		ALvoid* pData = static_cast<ALvoid*>(sData);
		alBufferData
		(
			*pBuffer,
			*pFormat,
			sData,
			iDataSize,
			iSampleRate
		);

		auxError = alGetError();
		if (auxError != AL_NO_ERROR)
		{

			return 0;
		}
		return new AudioBuffer(*pBuffer, sData);
	}
	else
	{
		return nullptr;
	}

}
uint32_t  AudioBuffer::getAlBuffer() const
{
	return m_uBuffer;
}