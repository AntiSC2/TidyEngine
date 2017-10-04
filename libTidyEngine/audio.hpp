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

#include "system.hpp"

struct ALCdevice_struct;
struct ALCcontext_struct;
typedef ALCdevice_struct ALCdevice;
typedef ALCcontext_struct ALCcontext;

class Audio: public ISystem {
public:
	Audio();
	~Audio();

	void Initialise();
	virtual void Execute();
	void Clean();
	const ALCdevice *GetDevice() const;
	virtual std::string GetType();
private:
	ALCdevice *m_Device = nullptr;
	ALCcontext *m_Context = nullptr;
};