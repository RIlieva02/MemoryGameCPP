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
#include "pugixml.hpp"
#include "pugiconfig.hpp"
#include "Deck.hpp"
#include "StatisticWindow.hpp"

class Game {
public:
    Game();
    ~Game();
    
    void setPlayerName(std::string);
    std::string getPlayerName();
    void setMoves(int);
    int getMoves();
    void setMistakes(int);
    int getMistakes();
    void setRandomNumber(int);
    int getRandomNumber();
    bool getResult();
    
    bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
    bool ttf_init();
    void render();
    void handleEvents();
    void clean();
    bool isRunning();
    
    // проверяваме дали текстурата е кликната
    bool isClickableTextureClicked(SDL_Texture* t, SDL_Rect* r, int xDown, int yDown);
    
    // проверява дали играта е приключила
    void isGameOver();
    
    // сетваме таймера
    void setTime(float);
    float getTime();
    
private:
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    
    bool running; // проверка дали играта продължава
    bool startButtonClicked; // проверка дали е кликнат старт бутона
    bool timeButtonsClicked; // проверка дали е кликнат бутон за време
    bool hintButtonClicked; // проверка дали е кликнат жокер бутона
    bool statisticButtonClicked; // проверка дали е кликнат бутона за статистиката
    bool openTwoPictures; // проверка дали са отворени два бутона
    bool gameOver; // проверка дали е приключила играта
    bool onTime; // дали е спазено времето за игра
    bool hint; // проверява дали е кликнат бутона за жокер
    

    SDL_Texture *gameNameText; // текст за началото на играта
    SDL_Rect gameNameRect; // координати за текста
    
    SDL_Texture *playerNameText, *playerNameStr; // текст за началото на играта
    SDL_Rect playerNameRect, playerNameStrRect; // координати на текста за начало на играта
    
    SDL_Texture *startButtonNameText, *hintButtonNameText, *statisticButtonNameText; // текст за бутоните
    SDL_Rect startButtonNameRect, hintButtonNameRect, statisticButtonNameRect; // координати на текста на бутоните
    
    // текст за бутоните за времето
    SDL_Texture *timeOneButtonNameText, *timeTwoButtonNameText, *timeFiveButtonNameText, *noTimeButtonNameText;
    // координати на текста на бутоните за времето
    SDL_Rect timeOneButtonNameRect, timeTwoButtonNameRect, timeFiveButtonNameRect, noTimeButtonNameRect;
    
    SDL_Texture *resultWinText, *resultLoseText; // текст за победа или загуба
    SDL_Rect resultWinRect, resultLoseRect; // координати на текст за победа или загуба
    
    std::string playerName; // съхранява името на играча
    
    SDL_Texture* background; // фон
    SDL_Rect backgroundRect; // координати на фона
    
    SDL_Texture* buttonStart, *buttonStop, *buttonHint, *buttonStatistic; // бутони
    SDL_Rect buttonStartRect, buttonStopRect, buttonHintRect, buttonStatisticRect; // координати на бутоните
    
    // бутони за времето
    SDL_Texture* buttonTimeOne, *buttonTimeTwo, *buttonTimeFive, *buttonNoTime;
    // координати на бутоните за времето
    SDL_Rect buttonTimeOneRect, buttonTimeTwoRect, buttonTimeFiveRect, buttonNoTimeRect;
    
    SDL_Rect fillRect1, fillRect2; // правоъгълник
    
    Deck* playingCards;// тестето с карти
    int randomNumber; // размер на тестето с карти
    
    Card* firstRevealedCard; // запазваме информацията за първата обърната карта
    Card* secondRevealedCard; // запазваме информация за втората обърната карта
    
    int moves, mistakes; //ходове и грешки
    
    // Таймер
    float time; // изминалото време в секунди
    int chosedTime; // избрано време от играча

};
#endif /* Game_hpp */
