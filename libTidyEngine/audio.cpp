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

#include "audio.hpp"
#include <cstdio>
#include <alc.h>
#include <al.h>

Audio::Audio()
{
	Initialise();
}

Audio::~Audio()
{
	Clean();
}

void Audio::Initialise()
{
	m_Device = alcOpenDevice(nullptr);
	m_Context = alcCreateContext(m_Device, nullptr);
	alcMakeContextCurrent(m_Context);

	int error = alcGetError(m_Device);
	if (error != ALC_NO_ERROR) {
		printf("Error: OpenAL %d\n", error);
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(m_Context);
		alcCloseDevice(m_Device);
		m_Context = nullptr;
		m_Device = nullptr;
	}
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
}

void Audio::Execute(bool fixed)
{
	;
}

void Audio::Clean()
{
	int error = alcGetError(m_Device);
	if (error != ALC_NO_ERROR) {
		printf("Error: OpenAL %d\n", error);
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(m_Context);
		alcCloseDevice(m_Device);
		m_Context = nullptr;
		m_Device = nullptr;
	}
	alcMakeContextCurrent(nullptr);	
	alcDestroyContext(m_Context);
	alcCloseDevice(m_Device);

	m_Context = nullptr;
	m_Device = nullptr;
}

const ALCdevice *Audio::GetDevice() const
{
	return m_Device;
}

std::string Audio::GetType()
{
	return "Audio";
}