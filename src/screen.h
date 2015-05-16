#pragma once
#include <SDL2/SDL.h>

//The screen class handles the SDL window and stores the width, height and the title of the window
class Screen {
    public:
        Screen();
        ~Screen();
        
        int getWidth();
        int getHeight();
        const char* getTitle();

        bool createNewWindow(int width, int height, const char* title);
    private:
        SDL_Window* m_Window = nullptr;
        int m_Width = 0;
        int m_Height = 0;
        char* m_Title = 0;
};
