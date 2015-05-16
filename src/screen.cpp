#include "screen.h"
#include <stdio.h>

//The screen constructor does nothing special, the destructor makes sure the window is destroyed
Screen::Screen() {
    ;
}

Screen::~Screen() {
   if(m_Window != nullptr) {
       SDL_DestroyWindow(m_Window);
       m_Window = nullptr;
   }
}

//getWidth and getHeight returns the width and the height of the window in form of a integer
inline int Screen::getWidth() {
    return m_Width;
}

inline int Screen::getHeight() {
    return m_Height;
}

//getTitle returns the title of the window in form of a constant character array
inline const char* Screen::getTitle() {
    return m_Title;
}

//createNewWindow destroyes the old window and creates a new one
//Returns true if a new window was created successfully
bool Screen::createNewWindow(int width, int height, const char* title) {
    bool success = true;
    if(m_Window != nullptr) {
        SDL_DestroyWindow(m_Window);
        m_Window = nullptr;
    }
    m_Width = width;
    m_Height = height;
    m_Title = const_cast<char*>(title);
    m_Window = SDL_CreateWindow(m_Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                m_Width, m_Height, SDL_WINDOW_SHOWN);
    if(m_Window == nullptr) {
        printf("Error 001: Window could not be created! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    return success;
}
