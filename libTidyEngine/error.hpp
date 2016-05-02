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

#include <exception>
#include <string>
#include <FreeImage.h>

class Error : public std::exception {
public:
	Error()
	{
		;
	}
	Error(std::string s)
	{
		text = s;
	}

	virtual const char *what() const noexcept
	{
		return text.c_str();
	}
private:
	std::string text = "";
};

void FreeImageError(FREE_IMAGE_FORMAT fif, const char *message);