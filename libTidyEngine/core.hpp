/*
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
*/

#pragma once

#include "screen.hpp"
#include "spriterenderer.hpp"
#include "modelrenderer.hpp"
#include "input.hpp"
#include "entitymanager.hpp"
#include "audio.hpp"
#include "font.hpp"

typedef struct FT_LibraryRec_ * FT_Library;

class Core {
public:
	Core();
	virtual ~Core();

	virtual void Run();
	bool m_Quit = false;
protected:
	virtual bool InitSubSystems();
	virtual bool Init() = 0;
	virtual void GameLoop();
	virtual void Update(double delta) = 0;
	virtual void DrawGame() = 0;
	virtual void Quit();

	bool m_Initialized = false;	
	Audio m_Audio;
	FT_Library m_FontLib;
	SpriteRenderer m_SpriteRenderer;
	ModelRenderer m_ModelRenderer;
	Input m_Input;
	Font m_Font;
	EntityManager m_EM;
};
