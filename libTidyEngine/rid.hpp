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
class Spritesheet;
class Shader;

enum class ID {None, Texture, Sample, Music, Font, Renderable, Spritesheet,
               Shader};

union ResourcePointers {
	ResourcePointers();
	~ResourcePointers();
	
	std::shared_ptr<Texture> tex;
	std::shared_ptr<Sample> sample;
//	Music *music:
//	Font *font;
	std::shared_ptr<Renderable> render;
	std::shared_ptr<Spritesheet> sheet;
	std::shared_ptr<Shader> shader;
};

class RID {
public:
	RID();
	~RID();

	ID State();
	std::shared_ptr<void> Data();
private:
	ID m_ID = ID::None;
	ResourcePointers m_Pointers;
};