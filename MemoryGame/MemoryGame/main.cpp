//
//  main.cpp
//  MemoryGame
//
//  Created by Ralitsa Toneva on 20.02.24.
//

#include <iostream>
#include "Game.hpp"

Game* game = NULL;
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 900;

int main(int argc, char* argv[]) {

    game = new Game();
    game->init("MEMORY GAME",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE);
    game->ttf_init();
    while (game->isRunning()) {
        game->handleEvents();
        game->render();
    }
    game->clean();
    
    return 0;
}
