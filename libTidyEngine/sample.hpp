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

#pragma once
#include <al.h>

class Sample {
public:
	Sample();
	Sample(int f, const void *d, size_t size, size_t freq);
	~Sample();

	void CreateBuffer(int f, const void *d, size_t size, size_t freq);
	void DestroyBuffer();
	unsigned int GetBuffer() const;
private:
	ALuint m_Buffer;
};