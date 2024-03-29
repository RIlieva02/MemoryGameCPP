//
//  StatisticWindow.hpp
//  MemoryGame
//
//  Created by Ralitsa Toneva on 25.02.24.
//

#ifndef StatisticWindow_hpp
#define StatisticWindow_hpp

#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

class StatisticWindow {
public:
    StatisticWindow(float, int, int);
    ~StatisticWindow();
    bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
    bool ttf_init();
    void render();
    void handleEvents();
    void clean();
    bool isRunning();
    bool isClickableTextureClicked(SDL_Texture* t, SDL_Rect* r, int xDown, int yDown);
    std::string intToString(int);
    
    void setTime(float);
    float getTime();
    int getOneSecTime();
    int getOneMinTime();
    
private:
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    
    TTF_Font* font;
    
    bool running; // проверка дали играта продължава
    bool closeButtonClicked; // проверка дали е кликнат бутонъ за затваряне
    
    SDL_Texture *gameNameText; // името на играта
    SDL_Rect gameNameRect; // координати за името на играта
    
    SDL_Texture *timeText; // текст за времето
    SDL_Rect timeTextRect; // координати за текста на времето
    
    SDL_Texture *timeInt; // времето
    SDL_Rect timeIntRect; // координати за времето
    
    SDL_Texture *movesText, *mistakesText; // текст за брой ходове и грешки
    SDL_Rect movesTextRect, mistakesTextRect; // координати на текста за брой ходове и грешки
    
    SDL_Texture *movesInt, *mistakesInt; // int за брой ходове и грешки
    SDL_Rect movesIntRect, mistakesIntRect; // координати за int брой ходове и грешки
    
    SDL_Texture* buttonClose; // бутон затвори
    SDL_Rect buttonCloseRect; // координати на бутоните
    
    SDL_Texture *closeButtonNameText; // текст за бутонa
    SDL_Rect closeButtonNameRect; // координати на текста за бутона
    
    int moves, mistakes; // ходове и грешки
    
    SDL_Texture* playerMoves, *playerMistakes; // текс за ходовете и грешките на играча
    SDL_Rect playerMovesRect, playerMistakesRect; // координати на текста и грешките
    
    // таймер
    float time;
    int sec; // секунди
    int min; // минути
    
//    int sec, min;
};
#endif /* StatisticWindow_hpp */
