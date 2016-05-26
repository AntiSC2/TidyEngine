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

AudioSystem::AudioSystem(bool create)
{
	if (create == true) {
		m_Device = alcOpenDevice(nullptr);
		m_Context = alcCreateContext(m_Device, nullptr);
		alcMakeContextCurrent(m_Context);
	}
}

AudioSystem::~AudioSystem()
{
	if (m_Context != nullptr)
		alcDestroyContext(m_Context);
	if (m_Device != nullptr)
		alcCloseDevice(m_Device);

	m_Context = nullptr;
	m_Device = nullptr;
}

const ALCdevice *AudioSystem::GetDevice() const
{
	return m_Device;
}