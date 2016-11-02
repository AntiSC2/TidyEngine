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

#include <memory>

class Texture;
class Sample;
class Renderable;
class Sheet;
class Shader;

enum class ID {None, Texture, Sample, Music, Font, Renderable, Sheet,
               Shader};

class RID {
public:
	RID();
	RID(ID id, void *data);
	~RID();

	ID State();
	void SetResource(Texture *res);
	void SetResource(Sample *res);
	void SetResource(Renderable *res);
	void SetResource(Sheet *res);
	void SetResource(Shader *res);
	void *Data();
private:
	ID m_ID = ID::None;
	std::shared_ptr<void> m_Data;
};