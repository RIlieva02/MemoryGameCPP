//
//  Game.hpp
//  MemoryGame
//
//  Created by Ralitsa Toneva on 20.02.24.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include "Deck.hpp"

class Game {
public:
    Game();
    ~Game();
    bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
    bool ttf_init();
    void render();
    void playgroundRender();
    void startGame();
    void update();
    void handleEvents();
    void clean();
    bool isRunning();
    bool isClickableTextureClicked(SDL_Texture* t, SDL_Rect* r, int xDown, int yDown);
    
private:
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    bool running;
    bool buttonClicked;
    bool showInitialScreen;
    bool pic;
    SDL_Texture *textTextureFont1, *textTextureFont2, *textTextureFont3;
    SDL_Rect dRectFont1, dRectFont2, dRectFont3;
    SDL_Texture* clickableTexture;
    SDL_Rect clickableRect;
    int mouseDownX, mouseDownY;
    std::string inputText; // въвеждане на името
    SDL_Texture* image1, *image2; // картинки
    SDL_Rect imageRect1, imageRect2;
    SDL_Rect fillRect1, fillRect2;
    Deck* playingCards;
    int randomNumber;
    Card* firstRevealedCard;
    Card* secondRevealedCard;
};
#endif /* Game_hpp */
