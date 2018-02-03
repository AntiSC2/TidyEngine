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