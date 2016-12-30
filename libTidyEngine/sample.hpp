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
#include <cstddef>
#include "resource.hpp"

class Sample: public Resource {
public:
	Sample();
	Sample(int format, const void *data, size_t size, size_t freq);
	~Sample();

	virtual std::string Type();

	bool CreateBuffer(int format, const void *data, size_t size,
	                  size_t freq);
	void DestroyBuffer();
	void Play() const;
	unsigned int GetBuffer() const;
	unsigned int GetSource() const;
private:
	ALuint m_Source;
	ALuint m_Buffer;
};
