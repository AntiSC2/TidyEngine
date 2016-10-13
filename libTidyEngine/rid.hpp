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

class Texture;
class Sample;
class Renderable;
class Spritesheet;
class Shader;

enum class ID {None, Texture, Sample, Music, Font, Renderable, Spritesheet,
               Shader};

union ResourcePointers {
	Texture *tex;
	Sample *sample;
//	Music *music:
//	Font *font;
	Renderable *render;
	Spritesheet *sheet;
	Shader *shader;
}

class RID {
public:
	RID();
	~RID();

	ID State();
	void *Data();
private:
	ID *m_ID = ID::None;
	ResourcePointers m_Pointers;
};
