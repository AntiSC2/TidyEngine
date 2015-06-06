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

#pragma once
#include <SDL2/SDL.h>
#include <vector>

//The input class handles mouse and key inputs given to the window
//It's a static class for the most part
class Input {
    public:
        Input();
        ~Input();
        
        void update();
        //Returns if the user has tried to close the window
        //True means that the user wants to close the window
        bool getCloseWindow() {
            return m_CloseWindow;
        }
        
        static bool getKeyPressed(SDL_Scancode scancode);
    private:
        bool m_CloseWindow = false;
        static std::vector<bool> m_PressedKeys;
};
