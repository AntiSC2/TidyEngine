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

Sample::Sample()
{
	;
}

Sample::Sample(int format, const void *data, size_t size, size_t bit_rate)
{
	CreateBuffer(format, data, size, bit_rate);
}

Sample::~Sample()
{
	DestroyBuffer();
}

void Sample::CreateBuffer(int format, const void *data, size_t size,
                          size_t bit_rate)
{
	if (alIsBuffer(m_Buffer) == AL_TRUE) {
		alDeleteBuffers(1, &m_Buffer);
		m_Buffer = 0;
	}

	alGenBuffers(1, &m_Buffer);
	alBufferData(m_Buffer, format, data, size, bit_rate);
}

void Sample::DestroyBuffer()
{
	if (alIsBuffer(m_Buffer) == AL_TRUE) {
		alDeleteBuffers(1, &m_Buffer);
		m_Buffer = 0;
	}
}

unsigned int Sample::GetBuffer() const
{
	return m_Buffer;
}
