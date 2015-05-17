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

//The screen class handles the SDL window and stores the width, height and the title of the window
class Screen {
    public:
        Screen();
        ~Screen();
        //getWidth & getHeight returns the width and height in px, getTitle returns the window title
        //getWindow returns the pointer to the actual window, getRenderer returns a pointer to the
        //renderer that renders the SDL textures to the screen 
        int getWidth() {
            return m_Width;
        }
        int getHeight() {
            return m_Height;
        }
        const char* getTitle() {
            return m_Title;
        }
        SDL_Window* getWindow() {
            return m_Window;
        }
        SDL_Renderer* getRenderer() {
            return m_Renderer;
        }
        bool createNewWindow(int width, int height, const char* title);
    private:
        SDL_Window* m_Window = nullptr;
        SDL_Renderer* m_Renderer = nullptr;
        int m_Width = 0;
        int m_Height = 0;
        char* m_Title = 0;
};
