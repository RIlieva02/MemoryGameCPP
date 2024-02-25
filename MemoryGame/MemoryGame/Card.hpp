//
//  Card.hpp
//  MemoryGame
//
//  Created by Ralitsa Toneva on 21.02.24.
//

#ifndef Card_hpp
#define Card_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

class Card {
public:
    Card(std::string, SDL_Texture*);
    
    void setId(std::string);
    std::string getId() const;
    
    SDL_Texture* getTexture();
    
    void setRect(int, int, int, int);
    SDL_Rect& getRect(); // връщам конст, защото подавам референтен тип
    
    void drawCard(int, int, int, int, SDL_Renderer*); // изкарваме една карта
    
    void hide(); // скриваме картата
    void reveal(); // показваме картата
    bool isHidden() const;  // показваме дали картата е скрита
    
    void clicked(); // кликваме картата
    bool isClicked() const; // показваме дали картата е кликната
    
    void clean();

private:
    std::string id; // номер на снимка
    SDL_Texture* image;// снимка
    SDL_Rect rect; // координати на снимката
    SDL_Renderer* cardRenderer = NULL;
    bool hidden; // проверява дали картинката е скрита
    bool click; // проверява дали картинката е кликната
};
#endif /* Card_hpp */
