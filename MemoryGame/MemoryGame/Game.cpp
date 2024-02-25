//
//  Game.cpp
//  MemoryGame
//
//  Created by Ralitsa Toneva on 20.02.24.
//

#include "Game.hpp"

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) {

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL init success\n";

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window != 0) //window init success
        {
            std::cout << "window creation success\n";
            renderer = SDL_CreateRenderer(window, -1, 0);
          //  playingCards->getRenderer() =  SDL_CreateRenderer(window, -1, 0);
            if (renderer != 0) //renderer init success
            {
                
                std::cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                // фон на играта
                background = IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Background/background.png");
                int ww, wh;
                SDL_GetWindowSize(window, &ww, &wh);
                SDL_QueryTexture(background, NULL, NULL, &backgroundRect.w, &backgroundRect.h);
                backgroundRect.x = 0;
                backgroundRect.y = 0;
                backgroundRect.w = ww;
                backgroundRect.h = wh;
                
                // показване на поле
                SDL_GetWindowSize(window, &ww, &wh);
                fillRect1 = { (ww / 2 - 300 / 2), ((wh / 2) + 50 / 2), 300, 50 };
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
                SDL_RenderFillRect(renderer, &fillRect1);
                
                // старт бутон
                SDL_RWops* start = SDL_RWFromFile("/Users/ralitsatoneva/Documents/MemoryGame/Background/button.png", "rb");
                buttonStart = IMG_LoadTexture_RW(renderer, start, 1);

                int tw, th;
                SDL_QueryTexture(buttonStart, 0, 0, &tw, &th);
                SDL_QueryTexture(buttonStart, NULL, NULL, &buttonStartRect.w, &buttonStartRect.h);
                buttonStartRect.x = (ww / 2 - 200 / 2);
                buttonStartRect.y = ((wh / 2) + (wh / 4) - 200 / 2);
                buttonStartRect.w = 200;
                buttonStartRect.h = 200;
                
                // поле за картите
                fillRect2 = { 0, 0, ww, wh };
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
                
                // картите
                playingCards = new Deck(renderer);
                
                // проверка дали старт бутона е кликнат (ако е сменяме сцените)
                startButtonClicked = false;
                
                // проверка дали са отворени две картинкинки
                openTwoPictures = false;
                
                // бутони на втория екран
                SDL_RWops* openCards = SDL_RWFromFile("/Users/ralitsatoneva/Documents/MemoryGame/Background/button.png", "rb");
                buttonHint = IMG_LoadTexture_RW(renderer, openCards, 1);

                SDL_QueryTexture(buttonHint, NULL, NULL, &buttonHintRect.w, &buttonHintRect.h);
                buttonHintRect.x = (ww - (ww / 4));
                buttonHintRect.y = (wh / 9) * 2;
                buttonHintRect.w = 300;
                buttonHintRect.h = 200;
                
                SDL_RWops* stat = SDL_RWFromFile("/Users/ralitsatoneva/Documents/MemoryGame/Background/button.png", "rb");
                buttonStatistic = IMG_LoadTexture_RW(renderer, stat, 1);

                SDL_QueryTexture(buttonStatistic, NULL, NULL, &buttonStatisticRect.w, &buttonStatisticRect.h);
                buttonStatisticRect.x = (ww - (ww / 4));
                buttonStatisticRect.y = (wh / 3) + ((wh / 9) * 2);
                buttonStatisticRect.w = 300;
                buttonStatisticRect.h = 200;
                
                //проверка дали е кликнат бутон за време
                timeButtonsClicked = false;
                // проверка дали е кликнат бутона жокер
                hint = false;
                // проверка дали е приключила играта
                gameOver = false;
                // проверка дали е спазено времето за игра
                onTime = false;

            }
            else {
                std::cout << "renderer init failed\n";
                return false;
            }
        }
        else {
            std::cout << "window init failed\n";
            return false;
        }
    }
    else {
        std::cout << "SDL init fail\n";
        return false;
    }
    std::cout << "init success\n";
    running = true;
    return true;
}

bool Game::ttf_init(){
    if (TTF_Init() == -1){
        return false;
    }
    // шрифт за името на играта
    TTF_Font* fontGame = TTF_OpenFont("/Users/ralitsatoneva/Documents/MemoryGame/Fonts/Arcade.ttf", 120);
    // шрифт за името на играча
    TTF_Font* fontPlayer = TTF_OpenFont("/Users/ralitsatoneva/Documents/MemoryGame/Fonts/Arcade.ttf", 40);
    // шрифт за името на бутона
    TTF_Font* fontButton = TTF_OpenFont("/Users/ralitsatoneva/Documents/MemoryGame/Fonts/Arcade.ttf", 30);
    // проверка
    if (fontGame == NULL || fontPlayer == NULL || fontButton == NULL){
        return false;
    }
    
    // деклариране и инициализация на текстовете
    SDL_Surface* game = NULL; // име на играта
    SDL_Surface* player = NULL; // текст за името на играча
    SDL_Surface* playerNameImp = NULL; // името на играча
    SDL_Surface* startButton = NULL; // име на старт бутона
    SDL_Surface* hintButton = NULL; // име на жокер бутона
    SDL_Surface* statisticButton = NULL; // име на бутона за статистиката
    SDL_Surface* resultWin = NULL; // тескт за победа
    SDL_Surface* resultLose = NULL; // текст за загуба
    
    // сцена 1
    // текст за името на играта
    game = TTF_RenderText_Blended(fontGame, "MEMORY GAME", {0, 0, 0, 0});
    gameNameText = SDL_CreateTextureFromSurface(renderer, game);

    // текст за името на играча
    player = TTF_RenderText_Blended(fontPlayer, "ENTER YOUR NAME", {0, 0, 0, 0});
    playerNameText = SDL_CreateTextureFromSurface(renderer, player);
    
    // името на играча
    playerNameImp = TTF_RenderText_Blended(fontPlayer, playerName.c_str(), {0, 0, 0, 0});
    playerNameStr = SDL_CreateTextureFromSurface(renderer, playerNameImp);
    
    // текст за името на старт бутона
    startButton = TTF_RenderText_Blended(fontButton, "START", {0, 0, 0, 0});
    startButtonNameText = SDL_CreateTextureFromSurface(renderer, startButton);
    
    // сцена 2
    // текст за името на жокер бутона
    hintButton = TTF_RenderText_Blended(fontButton, "HINT", {0, 0, 0, 0});
    hintButtonNameText = SDL_CreateTextureFromSurface(renderer, hintButton);
    
    // текст за името на бутона за статистиката
    statisticButton = TTF_RenderText_Blended(fontButton, "STATISTIC", {0, 0, 0, 0});
    statisticButtonNameText = SDL_CreateTextureFromSurface(renderer, statisticButton);
    
    // сцена 3
    // текст за победа
    resultWin = TTF_RenderText_Blended(fontGame, "WIN", {0, 0, 0, 0});
    resultWinText = SDL_CreateTextureFromSurface(renderer, resultLose);
    
    // текст за загуба
    resultLose = TTF_RenderText_Blended(fontGame, "LOSE", {0, 0, 0, 0});
    resultLoseText = SDL_CreateTextureFromSurface(renderer, resultLose);

    
    // позиция на текста
    int ww, wh; // големина на екрана (дължина и височина)
    SDL_GetWindowSize(window, &ww, &wh);

    int tw, th; // големина на текста (дължина и височина)
    // сцена 1
    // координати на теста за името на играта
    SDL_QueryTexture(gameNameText, 0, 0, &tw, &th);
    gameNameRect = { (ww / 2 - tw / 2), (wh / 3 - th / 2), tw, th };

    // координати за текста за името на играча
    SDL_QueryTexture(playerNameText, 0, 0, &tw, &th);
    playerNameRect = { (ww / 2 - tw / 2), (wh / 2 - th / 2), tw, th };
    
    // координати името на играча
    SDL_QueryTexture(playerNameStr, 0, 0, &tw, &th);
    playerNameStrRect = { (ww / 2 - tw/ 2), ((wh / 2) + (th / 2) * 2), tw, th };
    
    // координати за теста на старт бутона
    SDL_QueryTexture(startButtonNameText, 0, 0, &tw, &th);
    startButtonNameRect = { (ww / 2 - 200 / 2) + (200 - tw) / 2, ((wh / 2) + (wh / 4) - 200 / 2) + (200 - th) / 2, tw, th };
    
    // сцена 2
    // координати за текста на жокер бутона
    SDL_QueryTexture(hintButtonNameText, 0, 0, &tw, &th);
    hintButtonNameRect = { ww - (ww / 4) + (300 - tw) / 2, (wh / 9) * 2 + (200 - th) / 2, tw, th };
    
    // координати за текста на бутона за статистиката
    SDL_QueryTexture(statisticButtonNameText, 0, 0, &tw, &th);
    statisticButtonNameRect = { ww - (ww / 4) + (300 - tw) / 2, (wh / 3) + ((wh / 9) * 2 + (200 - th) / 2), tw, th };
    
    // сцена 3
    // координати за текста победа
    SDL_QueryTexture(resultWinText, 0, 0, &tw, &th);
    resultWinRect = { (ww / 2 - tw / 2), (wh / 2 - th / 2), tw, th };
    
    // координати за теста загъба
    SDL_QueryTexture(resultLoseText, 0, 0, &tw, &th);
    resultLoseRect = { (ww / 2 - tw / 2), (wh / 2 - th / 2), tw, th };
 
    SDL_FreeSurface(game);
    SDL_FreeSurface(player);
    
    SDL_FreeSurface(startButton);
    SDL_FreeSurface(hintButton);
    SDL_FreeSurface(statisticButton);
    
    SDL_FreeSurface(resultWin);
    SDL_FreeSurface(resultLose);
    
    TTF_CloseFont(fontGame);
    TTF_CloseFont(fontPlayer);
    TTF_CloseFont(fontButton);
    
    return true;
}

void Game::render() {
    SDL_RenderClear(renderer);
    
    // показване на фона
    SDL_RenderCopy(renderer, background, NULL, &backgroundRect);
    
    if (!startButtonClicked){   // сцена 1
        
        // показване на името на играта
        SDL_RenderCopy(renderer, gameNameText, NULL, &gameNameRect);
        // текст за името на играча
        SDL_RenderCopy(renderer, playerNameText, NULL, &playerNameRect);
        // показване на поле
        SDL_RenderFillRect(renderer, &fillRect1);
        // името на играча
        SDL_RenderCopy(renderer, playerNameStr, NULL, &playerNameStrRect);
        // показване на старт бутона
        SDL_RenderCopy(renderer, buttonStart, NULL, &buttonStartRect);
        // показване на текст "старт"
        SDL_RenderCopy(renderer, startButtonNameText, NULL, &startButtonNameRect);

    } else{ // сцена 2, 3 и 4
      
        // пред поле
        SDL_RenderFillRect(renderer, &fillRect2);
        
        if (!gameOver){ // проверяваме дали играта е приключила
            
            // проверяваме дали е кликант бутон за време
            if (!timeButtonsClicked){ // сцена 2
                // бутони за различното време
                
                
            }else { // сцена 3
                // принтиране на задната страна на картите
                playingCards->printBackCards();
                
                // принтене на картите
                playingCards->printDeck();
                
                // бутон за жокер
                SDL_RenderCopy(renderer, buttonHint, NULL, &buttonHintRect);
                // показване на текст "жокер"
                SDL_RenderCopy(renderer, hintButtonNameText, NULL, &hintButtonNameRect);
                
                // проверка дали е кликнат бутона hint
                if (hint){
                    playingCards->printHintDeck();
                }
                
                // бутон за статистика
                SDL_RenderCopy(renderer, buttonStatistic, NULL, &buttonStatisticRect);
                // показване на текст "статистика"
                SDL_RenderCopy(renderer, statisticButtonNameText, NULL, &statisticButtonNameRect);
            }
            
        }else { // сцена 4
            
            if(onTime){ // проверяваме дали е спазено времето
                
                // показване надпис за победа
                SDL_RenderCopy(renderer, resultWinText, NULL, &resultWinRect);
                
            }else {
                // показване надпис за загуба
                SDL_RenderCopy(renderer, resultLoseText, NULL, &resultLoseRect);
            }
            
        }
            
    }
    
    SDL_RenderPresent(renderer);
}

bool Game::isClickableTextureClicked(SDL_Texture* t, SDL_Rect* r, int xDown, int yDown){
    if ((xDown > r->x && xDown < (r->x + r->w)) &&
         (yDown > r->y && yDown < (r->y + r->h))){
        return true;
    }
    return false;
}

void Game::handleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: running = false; break;
            case SDL_MOUSEBUTTONDOWN: {
                int msx, msy;
                if (event.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&msx, &msy);
                    
                    if (startButtonClicked == false){ // проверка дали е кликнат старт бутона
                        
                        if (isClickableTextureClicked(buttonStart, &buttonStartRect, msx, msy)) {
                            
                            std::cout << "CLICKED" << std::endl;
                            
                            startButtonClicked = true; // превключва от една сцена на друга
                            // генериране на картите за играта
                            randomNumber = playingCards->generateRandomNumber();
                            playingCards->startGame(randomNumber);
                            playingCards->shuffleDeck();
                            playingCards->printDeck();
                        } else {
                            
                            std::cout << "NOT" << std::endl;
                            
                            startButtonClicked = false;
                        }
                        
                    } else {
                        
                        if (!openTwoPictures){ // проверка дали са кликнати две карти
                            
                            // Проверка дали кликването е върху картата и тя е скрита
                            for (auto it = playingCards->getPlayingDeckOfCards().begin();
                                 it != playingCards->getPlayingDeckOfCards().end(); ++it){
                                if (isClickableTextureClicked(it->getTexture(), &it->getRect(), msx, msy)){
                                    it->reveal(); // откриваме картата
                                    it->clicked(); // кликваме върху нея
                                    
                                    if (firstRevealedCard != nullptr){
                                        secondRevealedCard = &(*it);
                                        openTwoPictures = true;
                            
                                    } else{
                                        firstRevealedCard = &(*it);
                                    }
                                    break; // намирам си картинката и спирам да въртя цикъла
                                }
                            }
                            
                            // проверка дали е кликнат бутонът жокер
                            if (isClickableTextureClicked(buttonHint, &buttonHintRect, msx, msy)) {
                                std::cout << "HINT CLICKED" << std::endl;
                                hint = true;
                                playingCards->printHintDeck();
                            }
                            
                            // проверка дали е кликнат бутонът за статистика
                            if (isClickableTextureClicked(buttonStatistic, &buttonStatisticRect, msx, msy)) {
                                std::cout << "STATISTIC CLICKED" << std::endl;
                                
                                // създаваме нов прозорец
                                StatisticWindow* statistic = NULL;
                                const int WINDOW_WIDTH = 400;
                                const int WINDOW_HEIGHT = 400;
                                statistic = new StatisticWindow(getTime(), moves, mistakes);
                                statistic->init("STATISTIC",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    WINDOW_WIDTH, WINDOW_HEIGHT,
                                    SDL_WINDOW_RESIZABLE);
                                statistic->ttf_init();
                                do{
                                    statistic->render();
                                    statistic->handleEvents();
                                }while (statistic->isRunning());
                                    
                                statistic->clean();
                            }
                        }
                    }
                }
            }; break;
            case SDL_MOUSEBUTTONUP: {
                int msx, msy;
                if (event.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&msx, &msy);
                    if (firstRevealedCard != nullptr && secondRevealedCard != nullptr) {
                        if (firstRevealedCard->getId() == secondRevealedCard->getId()) {
                            // картите са еднакви
                            
                            isGameOver(); // приключва играта ако всички карти са отворени
                    
                            firstRevealedCard = nullptr;
                            secondRevealedCard = nullptr;
                            openTwoPictures = false;
                            
                            moves++; // + 1 ход

                        } else {
                            SDL_Delay(500); // забавяне при скриването на картите с 0.5 секунди
                            // картите са различни
                            
                            moves++; // + 1 ход
                            mistakes++; // + 1 грешка
                            
                            firstRevealedCard->hide(); // скриваме първата карта
                            secondRevealedCard->hide(); // скриваме втората карта

                            firstRevealedCard = nullptr;
                            secondRevealedCard = nullptr;
                            openTwoPictures = false;
                            
                           
                        }
                    }
                    if (isClickableTextureClicked(buttonHint, &buttonHintRect, msx, msy)) {
                        std::cout << "HINT NOT CLICKED" << std::endl;
                        hint = false;
                    }
                }
            }; break;
            case SDL_TEXTINPUT: { // въвеждане от клавиатурата
                if (!startButtonClicked) { // Проверка дали екранът е сцена 1
                    
                    //  използваме само букви, цифри и интервали
                    if ((event.text.text[0] >= 'a' && event.text.text[0] <= 'z') ||
                        (event.text.text[0] >= 'A' && event.text.text[0] <= 'Z') ||
                        (event.text.text[0] >= '0' && event.text.text[0] <= '9') ||
                        (event.text.text[0] == ' ')) {
                        
                        // добавяме въведения символ към името
                        playerName += event.text.text[0];
                        ttf_init(); // извикваме, за да създаде големината, шрифта и координатите на текста
                        
                    }
                }
            }; break;
            
    
            default: break;
        }
    }
}

// сетване на времето
void Game::setTime(float time){
    this->time = time;
}
float Game::getTime(){
    return time;
}


// приключва играта ако са отворени всички карти
void Game::isGameOver(){
    // брояч на отворени карти
    int count = 0;
    
    for (auto it = playingCards->getPlayingDeckOfCards().begin(); it != playingCards->getPlayingDeckOfCards().end(); ++it){
        if (it->isHidden() == false){
            count++;
        }
    }
    
    // проверка дали размера е равен на отворените карти
    if (count == randomNumber){
        gameOver = true;
    }
    
}

void Game::setPlayerName(std::string name){
    this->playerName = name;
}
std::string Game::getPlayerName(){
    return this->playerName;
}
void Game::setMoves(int moves){
    this->moves = moves;
}
int Game::getMoves(){
    return this->moves;
}
void Game::setMistakes(int mistakes){
    this->mistakes = mistakes;
}
int Game::getMistakes(){
    return this->mistakes;
}
void Game::setRandomNumber(int randomNum){
    this->randomNumber = randomNum;
}
int Game::getRandomNumber(){
    return this->randomNumber;
}
bool Game::getResult(){
    if (onTime){
        return true; // 1
    }
    else {
        return false; // 0
    }
}

// изчистваме SDL
void Game::clean() {
    std::cout << "cleaning game\n";
    SDL_DestroyTexture(gameNameText);
    SDL_DestroyTexture(playerNameText);
    SDL_DestroyTexture(startButtonNameText);
    SDL_DestroyTexture(hintButtonNameText);
    SDL_DestroyTexture(statisticButtonNameText);
    
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(buttonStart);
    SDL_DestroyTexture(buttonHint);
    SDL_DestroyTexture(buttonStatistic);
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();
}

bool Game::isRunning() {
    return Game::running;
}

Game::Game() : firstRevealedCard(nullptr), secondRevealedCard(nullptr) {
    Game::window = NULL;
    Game::renderer = NULL;
    Game::running = true;
    
    Game::moves = 0; // ходове
    Game::mistakes = 0; // грешки
    
    Game::time = 0; // изминало време от началото на играта в секунди
}

Game::~Game() {
    clean();
   
    delete playingCards;
}

