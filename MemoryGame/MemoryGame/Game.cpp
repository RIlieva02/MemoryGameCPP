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
                image1 = IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Background/background.png");
                int ww, wh;
                SDL_GetWindowSize(window, &ww, &wh);
                SDL_QueryTexture(image1, NULL, NULL, &imageRect1.w, &imageRect1.h);
                imageRect1.x = 0;
                imageRect1.y = 0;
                imageRect1.w = ww;
                imageRect1.h = wh;
                
                // показване на поле
                SDL_GetWindowSize(window, &ww, &wh);
                fillRect1 = { (ww / 2 - 300 / 2), ((wh / 2) + 50 / 2), 300, 50 };
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
                SDL_RenderFillRect(renderer, &fillRect1);
                
                // старт бутон
                SDL_RWops* rw = SDL_RWFromFile("/Users/ralitsatoneva/Documents/MemoryGame/Background/button.png", "rb");
                image2 = IMG_LoadTexture_RW(renderer, rw, 1);

                SDL_QueryTexture(image2, NULL, NULL, &imageRect2.w, &imageRect2.h);
                imageRect2.x = (ww / 2 - 200 / 2);
                imageRect2.y = ((wh / 2) + (wh / 4) - 200 / 2);
                imageRect2.w = 200;
                imageRect2.h = 200;
                
                // поле за картите
                fillRect2 = { 0, 0, ww, wh };
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
                
                // картите
                playingCards = new Deck(renderer);
                randomNumber = playingCards->generateRandomNumber();
                playingCards->startGame(randomNumber);
                playingCards->shuffleDeck();
                playingCards->printDeck();
                
                // показване на екраните
                showInitialScreen = true;
                pic = true;

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
    // шрифтове и големина
    TTF_Font* font1 = TTF_OpenFont("/Users/ralitsatoneva/Documents/MemoryGame/Fonts/Arcade.ttf", 100);
    if (font1 == NULL){
        return false;
    }
    
    TTF_Font* font2 = TTF_OpenFont("/Users/ralitsatoneva/Documents/MemoryGame/Fonts/Arcade.ttf", 30);
    if (font2 == NULL){
        return false;
    }
    
    TTF_Font* font3 = TTF_OpenFont("/Users/ralitsatoneva/Documents/MemoryGame/Fonts/Arcade.ttf", 20);
    if (font3 == NULL){
        return false;
    }
    
    // деклариране и инициализация на текста
    SDL_Surface* tempSurfaceText1 = NULL;
    SDL_Surface* tempSurfaceText2 = NULL;
    SDL_Surface* tempSurfaceText3 = NULL;
    
    tempSurfaceText1 = TTF_RenderText_Blended(font1, "MEMORY GAME", {0, 0, 0, 0});
    textTextureFont1 = SDL_CreateTextureFromSurface(renderer, tempSurfaceText1);

    tempSurfaceText2 = TTF_RenderText_Blended(font2, "ENTER YOUR NAME", {0, 0, 0, 0});
    textTextureFont2 = SDL_CreateTextureFromSurface(renderer, tempSurfaceText2);
    
    tempSurfaceText3 = TTF_RenderText_Blended(font2, "START", {0, 0, 0, 0});
    textTextureFont3 = SDL_CreateTextureFromSurface(renderer, tempSurfaceText3);

    // позиция на текста
    int ww, wh;
    SDL_GetWindowSize(window, &ww, &wh);

    int tw, th;
    SDL_QueryTexture(textTextureFont1, 0, 0, &tw, &th);
    dRectFont1 = { (ww / 2 - tw / 2), (wh / 3 - th / 2), tw, th };

    SDL_QueryTexture(textTextureFont2, 0, 0, &tw, &th);
    dRectFont2 = { (ww / 2 - tw / 2), (wh / 2 - th / 2), tw, th };
    
    SDL_QueryTexture(textTextureFont3, 0, 0, &tw, &th);
    dRectFont3 = { (ww / 2 - 200 / 2) + (200 - tw) / 2,
                    ((wh / 2) + (wh / 4) - 200 / 2) + (200 - th) / 2,
                    tw, th };
 
    SDL_FreeSurface(tempSurfaceText1);
    SDL_FreeSurface(tempSurfaceText2);
    SDL_FreeSurface(tempSurfaceText3);
    TTF_CloseFont(font1);
    TTF_CloseFont(font2);
    TTF_CloseFont(font3);
    
    return true;
}

void Game::render() {
    SDL_RenderClear(renderer);
    
    if (showInitialScreen){
        // показване на фона
        SDL_RenderCopy(renderer, image1, NULL, &imageRect1);
        // показване на текста
        SDL_RenderCopy(renderer, textTextureFont1, NULL, &dRectFont1);
        SDL_RenderCopy(renderer, textTextureFont2, NULL, &dRectFont2);
        // показване на поле
        SDL_RenderFillRect(renderer, &fillRect1);
        // показване на старт бутона
        SDL_RenderCopy(renderer, image2, NULL, &imageRect2);
        // показване на текст "стар"
        SDL_RenderCopy(renderer, textTextureFont3, NULL, &dRectFont3);
        
        if (buttonClicked == true){
            showInitialScreen = false;
        }
    }
    else{
        // показване на поле
        SDL_RenderCopy(renderer, image1, NULL, &imageRect1);
        // пред поле
        SDL_RenderFillRect(renderer, &fillRect2);
        // принтиране на задната страна на картите
        playingCards->printBackCards();
        // принтене на картите
        playingCards->printDeck();
        // buttonClicked == false;
    }
    
    SDL_RenderPresent(renderer);
}

bool Game::isClickableTextureClicked(SDL_Texture* t, SDL_Rect* r, int xDown, int yDown){

//    (r->x) (r->x + tw)
//    (r->y) (r->y + th)

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
                    mouseDownX = msx;
                    mouseDownY = msy;
                    
                    if (!buttonClicked) { // Проверка дали бутона не е бил кликнат преди това
                        if (isClickableTextureClicked(image2, &imageRect2, mouseDownX, mouseDownY)) {
                            std::cout << "CLICKED" << std::endl;
                            buttonClicked = true;
                        } else {
                            std::cout << "NOT" << std::endl;
                            buttonClicked = false;
                        }
                    }
                }
            }; break;
            case SDL_MOUSEBUTTONUP: {
                int msx, msy;
                if (event.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&msx, &msy);
                    if (pic == true){
                        // Проверка дали кликването е върху картата и тя е скрита
                        for (auto it = playingCards->getPlayingDeckOfCards().begin();
                             it != playingCards->getPlayingDeckOfCards().end(); ++it){
                            if (isClickableTextureClicked(it->getTexture(), &it->getRect(), msx, msy)){
                                it->reveal();
                                if (firstRevealedCard != nullptr){
                                    secondRevealedCard = &(*it);
                                    pic = false;
                                    
                                    std::cout << "2 " << secondRevealedCard->getId() << std::endl;
                                }
                                else{
                                    firstRevealedCard = &(*it);
                                    std::cout << "1 " << firstRevealedCard->getId() << std::endl;
                                }
                                break; // намирам си картинката и спирам да въртя цикъла
                            }
                        }
                    }
                    else{
                       //  Проверка дали има две разкрити карти и дали те са еднакви
                        if (firstRevealedCard != nullptr && secondRevealedCard != nullptr) {
                            if (firstRevealedCard->getId() == secondRevealedCard->getId()) {
                                // картите са еднакви
                                firstRevealedCard = nullptr;
                                secondRevealedCard = nullptr;
                                pic = true;

                            } else {
                                // картите са различни
                                firstRevealedCard->hide();
                                secondRevealedCard->hide();

                                firstRevealedCard = nullptr;
                                secondRevealedCard = nullptr;
                                pic = true;
                            }
                        }
                    }
                }
            }; break;
    
            default: break;
        }
    }
}

void Game::update() {

}

void Game::clean() {
    std::cout << "cleaning game\n";
    SDL_DestroyTexture(textTextureFont1);
    SDL_DestroyTexture(textTextureFont2);
    SDL_DestroyTexture(textTextureFont3);
    SDL_DestroyTexture(clickableTexture);
    SDL_DestroyTexture(image1);
    SDL_DestroyTexture(image2);
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
}

Game::~Game() {

}
