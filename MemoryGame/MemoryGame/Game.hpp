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
#include "StatisticWindow.hpp"

class Game {
public:
    Game();
    ~Game();
    bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
    bool ttf_init();
    void render();
    void update();
    void handleEvents();
    void clean();
    bool isRunning();
    bool isClickableTextureClicked(SDL_Texture* t, SDL_Rect* r, int xDown, int yDown);
    void isGameOver();
    
private:
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    
    bool running; // проверка дали играта продължава
    bool startButtonClicked; // проверка дали е кликнат старт бутона
    bool hintButtonClicked; // проверка дали е кликнат жокер бутона
    bool statisticButtonClicked; // проверка дали е кликнат бутона за статистиката
    bool openTwoPictures; // проверка дали са отворени два бутона
    bool gameOver; // проверка дали е приключила играта
    bool onTime; // дали е спазено времето за игра
    
    SDL_Texture *gameNameText, *playerNameText; // текст за началото на играта
    SDL_Rect gameNameRect, playerNameRect; // координати за текста
    
    SDL_Texture *startButtonNameText, *hintButtonNameText, *statisticButtonNameText; // текст за бутоните
    SDL_Rect startButtonNameRect, hintButtonNameRect, statisticButtonNameRect; // координати на текста на бутоните
    
    SDL_Texture *resultWinText, *resultLoseText; // текст за победа или загуба
    SDL_Rect resultWinRect, resultLoseRect; // координати на текст за победа или загуба
    
    int mouseDownX, mouseDownY; // координати на мишката
    
    std::string playerName; // съхранява името на играча
    
    SDL_Texture* background; // фон
    SDL_Rect backgroundRect; // координати на фона
    
    SDL_Texture* buttonStart, *buttonStop, *buttonHint, *buttonStatistic; // бутони
    SDL_Rect buttonStartRect, buttonStopRect, buttonHintRect, buttonStatisticRect; // координати на бутоните
    
    SDL_Rect fillRect1, fillRect2;
    
    Deck* playingCards;// тестето с карти
    int randomNumber; // размер на тестето с карти
    
    Card* firstRevealedCard; // запазваме информацията за първата обърната карта
    Card* secondRevealedCard; // запазваме информация за втората обърната карта
    
    int moves, mistakes; //ходове и грешки

};
#endif /* Game_hpp */
