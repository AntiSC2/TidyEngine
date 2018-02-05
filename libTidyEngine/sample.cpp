/*
 * TidyEngine
 * Copyright (c) 2018 Jakob Sinclair <sinclair.jakob@mailbox.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "sample.hpp"
#include <al.h>
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

std::string Sample::Type() {
	return "Sample";
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
