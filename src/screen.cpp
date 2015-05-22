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

#include "screen.h"
#include <stdio.h>

//The screen constructor does nothing special, the destructor makes sure the window & the renderer
//is destroyed
Screen::Screen() {
    ;
}

Screen::~Screen() {
   if(m_Window != nullptr) {
       SDL_DestroyWindow(m_Window);
       m_Window = nullptr;
   }
   if(m_Renderer != nullptr) {
       SDL_DestroyRenderer(m_Renderer);
       m_Renderer = nullptr;
   }
}

//Returns true if a new window was created successfully, also creates a new renderer
bool Screen::createNewWindow(int width, int height, const char* title) {
    bool success = true;
    if(m_Window != nullptr) { //Destroy old window if it exists
        SDL_DestroyWindow(m_Window);
        m_Window = nullptr;
    }
    if(m_Renderer != nullptr) { //Destroy old renderer if it exists
        SDL_DestroyRenderer(m_Renderer);
        m_Renderer = nullptr;
    }
    m_Width = width;
    m_Height = height;
    m_Title = const_cast<char*>(title);
    m_Window = SDL_CreateWindow(m_Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                m_Width, m_Height, SDL_WINDOW_SHOWN);
    if(m_Window == nullptr) { //Check for errors, in the window creation part
        printf("Error 001: Window could not be created! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    if(success == true) { //Check for errors, in the renderer creation part
        m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
        if(m_Renderer == nullptr) {
            printf("Error 004: Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;    
        } else {
            SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        }
    }
    return success;
}
