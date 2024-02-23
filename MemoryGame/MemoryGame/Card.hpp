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
#include <map>
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
    void drawCard(int, int, int, int, SDL_Renderer*);
    void hide();
    void reveal();
    // Метод, който връща дали картата е скрита
    bool isHidden() const;

private:
    std::string id; // номер на снимка
    SDL_Texture* image;// снимка
    SDL_Rect rect;
    SDL_Renderer* cardRenderer = NULL;
    bool hidden;
    
};
#endif /* Card_hpp */
