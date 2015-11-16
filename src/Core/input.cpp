/*
Copyright (C) 2015 Jakob Sinclair

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

#include "input.h"

std::vector<bool> Input::m_PressedKeys;

//The constructor and destructor does nothing special
Input::Input() {
	for(size_t i = 0; i < 282; i++) {
		m_PressedKeys.push_back(false);
	}
}

Input::~Input() {
	;
}

//The update function loops through every new event
//If an event is detected it stores the data
void Input::update() {
	SDL_Event e;
	while(SDL_PollEvent(&e) != 0) {
		switch(e.type) {
			case SDL_QUIT:
				m_CloseWindow = true;
				break;
			case SDL_KEYDOWN:
				m_PressedKeys[e.key.keysym.scancode] = true;
				break;
			case SDL_KEYUP:
				m_PressedKeys[e.key.keysym.scancode] = false;
				break;
		}
	}
}

bool Input::getKeyPressed(SDL_Scancode key) {
	return m_PressedKeys[key];
}
