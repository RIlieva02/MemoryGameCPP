//
//  StatisticWindow.cpp
//  MemoryGame
//
//  Created by Ralitsa Toneva on 25.02.24.
//

#include "StatisticWindow.hpp"
bool StatisticWindow::init(const char* title, int xpos, int ypos, int width, int height, int flags) {

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
                SDL_SetRenderDrawColor(renderer, 153, 255, 153, 0);
                
                // координати на екрана
                int ww, wh;
                SDL_GetWindowSize(window, &ww, &wh);
                
                // бутон за затваряне на статистиката
                buttonClose = IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Background/button.png");

                SDL_QueryTexture(buttonClose, NULL, NULL, &buttonCloseRect.w, &buttonCloseRect.h);
                buttonCloseRect.x = (ww / 2 - 200 / 2);
                buttonCloseRect.y = ((wh / 2) + (wh / 4) + (wh / 4) / 2 - 200 / 2);
                buttonCloseRect.w = 200;
                buttonCloseRect.h = 200;
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

bool StatisticWindow::ttf_init(){
    if (TTF_Init() == -1){
        return false;
    }
    // шрифт за тестовете на екрана
    TTF_Font* font = TTF_OpenFont("/Users/ralitsatoneva/Documents/MemoryGame/Fonts/Arcade.ttf", 40);
    // проверка
    if (font == NULL){
        return false;
    }
    
    // деклариране и инициализация на текстовете
    SDL_Surface* gameName = NULL; // име на играта
    SDL_Surface* time = NULL;// време
    SDL_Surface* movesTxt = NULL; // текст ходове
    SDL_Surface* moves = NULL; // ходове
    SDL_Surface* mistakesTxt = NULL; // текст грешки
    SDL_Surface* mistakes = NULL; // грешки
    SDL_Surface* closeButton = NULL; // име на старт бутона
   
    // тест за името на играта
    gameName = TTF_RenderText_Blended(font, "MEMORY GAME", {0, 0, 0, 0});
    gameNameText = SDL_CreateTextureFromSurface(renderer, gameName);
    
    // тест за таймера
    time = TTF_RenderText_Blended(font, "TIME: ", {0, 0, 0, 0});
    timeText = SDL_CreateTextureFromSurface(renderer, time);
    
    // текста за брояча на ходове
    movesTxt = TTF_RenderText_Blended(font, "MOVES: ", {0, 0, 0, 0});
    movesText = SDL_CreateTextureFromSurface(renderer, movesTxt);
    
    // брояч на ходове
    std::string movesIntToString = intToString(this->moves);
    moves = TTF_RenderText_Blended(font, movesIntToString.c_str(), {0, 0, 0, 0});
    movesInt = SDL_CreateTextureFromSurface(renderer, moves);
    
    // текста за брояза на грешки
    mistakesTxt = TTF_RenderText_Blended(font, "MISTAKES: ", {0, 0, 0, 0});
    mistakesText = SDL_CreateTextureFromSurface(renderer, mistakesTxt);
    
    // брояч на грешки
    std::string mistakesIntToString= intToString(this->mistakes);
    mistakes = TTF_RenderText_Blended(font, mistakesIntToString.c_str(), {0, 0, 0, 0});
    mistakesInt = SDL_CreateTextureFromSurface(renderer, mistakes);
    
    // тест за затварящия бутон
    closeButton = TTF_RenderText_Blended(font, "CLOSE", {0, 0, 0, 0});
    closeButtonNameText = SDL_CreateTextureFromSurface(renderer, closeButton);

    // позиция на текста
    int ww, wh;
    SDL_GetWindowSize(window, &ww, &wh);

    int tw, th;
    // позиция за текста на името на играта
    SDL_QueryTexture(gameNameText, 0, 0, &tw, &th);
    gameNameRect = { (ww / 2 - tw / 2), (wh / 6 - th / 2), tw, th };
    
    // позиция за текста на таймера
    SDL_QueryTexture(timeText, 0, 0, &tw, &th);
    timeRect = { (ww / 4 - 10 - tw / 2), ((wh / 2) - (wh / 4) / 2 - th / 2), tw, th };
    
    // позиция на текста за ходовете
    SDL_QueryTexture(movesText, 0, 0, &tw, &th);
    movesTextRect = { (ww / 4 - tw / 2), (wh / 2 - th / 2), tw, th };
    
    // позицията на брояча за ходове
    SDL_QueryTexture(movesInt, 0, 0, &tw, &th);
    movesIntRect = { ((ww / 2) + (ww / 4) - (tw / 2)), (wh / 2 - th / 2), tw, th };
    
    // позицията на тескта за грешки
    SDL_QueryTexture(mistakesText, 0, 0, &tw, &th);
    mistakesTextRect = { (ww / 3 - tw / 2), ((wh / 2) + (wh / 4) / 2 - th / 2), tw, th };
    
    // позицията на брояча на грешки
    SDL_QueryTexture(mistakesInt, 0, 0, &tw, &th);
    mistakesIntRect = { ((ww / 2) + (ww / 4) - (tw / 2)), ((wh / 2) + (wh / 4) / 2 - th / 2), tw, th };
    
    // позицията на бутона за затваряне
    SDL_QueryTexture(closeButtonNameText, 0, 0, &tw, &th);
    closeButtonNameRect = { (ww / 2 - 200 / 2) + (200 - tw) / 2,
                    ((wh / 2) + (wh / 4) + (wh / 4) / 2 - 200 / 2) + (200 - th) / 2,
                    tw, th };

    // изчистване
    SDL_FreeSurface(gameName);
    SDL_FreeSurface(time);
    SDL_FreeSurface(moves);
    SDL_FreeSurface(mistakes);
    SDL_FreeSurface(closeButton);
   
    TTF_CloseFont(font);

    return true;
}

void StatisticWindow::render() {
    SDL_RenderClear(renderer);
    
    // показване на името на играта
    SDL_RenderCopy(renderer, gameNameText, NULL, &gameNameRect);
    
    // показване на времето
    SDL_RenderCopy(renderer, timeText, NULL, &timeRect);
   
    // показване на ходовете
    SDL_RenderCopy(renderer, movesText, NULL, &movesTextRect);
    
    SDL_RenderCopy(renderer, movesInt, NULL, &movesIntRect);
    
    // показване на грешките
    SDL_RenderCopy(renderer, mistakesText, NULL, &mistakesTextRect);
    
    SDL_RenderCopy(renderer, mistakesInt, NULL, &mistakesIntRect);
    
    // показване на старт бутона
    SDL_RenderCopy(renderer, buttonClose, NULL, &buttonCloseRect);
    // показване на текст "старт"
    SDL_RenderCopy(renderer, closeButtonNameText, NULL, &closeButtonNameRect);
    
    SDL_RenderPresent(renderer);
}

std::string StatisticWindow::intToString(int number) {
    std::stringstream ss;
    ss << number;
    return ss.str();
}

bool StatisticWindow::isClickableTextureClicked(SDL_Texture* t, SDL_Rect* r, int xDown, int yDown){
    if ((xDown > r->x && xDown < (r->x + r->w)) &&
         (yDown > r->y && yDown < (r->y + r->h))){
        return true;
    }
    return false;
}
void StatisticWindow::handleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: running = false; break;
            case SDL_MOUSEBUTTONDOWN: {
                int msx, msy;
                if (event.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&msx, &msy);
                        
                    if (isClickableTextureClicked(buttonClose, &buttonCloseRect, msx, msy)) {
                        std::cout << "CLICKED" << std::endl;
                        running = false;
                    }
                }
            }; break;
    
            default: break;
        }
    }
}

void StatisticWindow::clean() {
    std::cout << "cleaning game\n";
    SDL_DestroyTexture(gameNameText);
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

bool StatisticWindow::isRunning() {
    return StatisticWindow::running;
}

StatisticWindow::StatisticWindow(int moves, int mistake): moves(moves), mistakes(mistake){
    StatisticWindow::window = NULL;
    StatisticWindow::renderer = NULL;
    StatisticWindow::running = true;
}

StatisticWindow::~StatisticWindow() {
    clean();
}
