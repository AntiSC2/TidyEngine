#pragma once
#include "screen.h"

//This class is not part of the engine! It's just for testing
//The game class is the actual game, it makes sure that everything gets initialized and that
//everything gets updated and rendered

class Game {
    public:
        Game();
        ~Game();
        
        void run();
    private:
        void init();
        void gameLoop();
        void update();
        void drawGame();
        void quit();

        Screen m_Screen;
};
