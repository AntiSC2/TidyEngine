/*
TidyEngine
Copyright (C) 2016 Jakob Sinclair

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
Contact the author at: jakob.sinclair99@gmail.com
*/

#include "sample.hpp"
#include <stdio.h>

Sample::Sample()
{
	;
}

Sample::Sample(int format, const void *data, size_t size, size_t freq)
{
	CreateBuffer(format, data, size, freq);
}

Sample::~Sample()
{
	DestroyBuffer();
}

bool Sample::CreateBuffer(int format, const void *data, size_t size,
                          size_t freq)
{
	if (alIsBuffer(m_Buffer) == AL_TRUE) {
		alDeleteBuffers(1, &m_Buffer);
		m_Buffer = 0;
	}
	if (alIsSource(m_Source) == AL_TRUE) {
		alDeleteSources(1, &m_Source);
		m_Source = 0;
	}

	alGenBuffers(1, &m_Buffer);
	alBufferData(m_Buffer, format, data, size, freq);
	
	int error = alGetError();
	if (error != AL_NO_ERROR) {
		printf("OpenAL error: %d\n", error);
		alDeleteBuffers(1, &m_Buffer);
		m_Buffer = 0;
		return false;
	}

	alGenSources(1, &m_Source);

	error = alGetError();
	if (error != AL_NO_ERROR) {
		printf("OpenAL error: %d\n", error);
		alDeleteSources(1, &m_Source);
		m_Source = 0;
		return false;
	}

	alSourceQueueBuffers(m_Source, 1, &m_Buffer);
	alSource3f(m_Source, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(m_Source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	return true;
}

void Sample::DestroyBuffer()
{
	if (alIsSource(m_Source) == AL_TRUE) {
		alSourcei(m_Source, AL_BUFFER, 0);
		alDeleteSources(1, &m_Source);
		m_Source = 0;
	}
	if (alIsBuffer(m_Buffer) == AL_TRUE) {
		alDeleteBuffers(1, &m_Buffer);
		m_Buffer = 0;
	}

}

void Sample::Play() const
{
	alSourcePlay(m_Source);
}

unsigned int Sample::GetBuffer() const
{
	return m_Buffer;
}

unsigned int Sample::GetSource() const
{
	return m_Source;
}
