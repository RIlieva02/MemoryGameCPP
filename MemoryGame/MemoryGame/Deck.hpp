//
//  Deck.hpp
//  MemoryGame
//
//  Created by Ralitsa Toneva on 21.02.24.
//

#ifndef Deck_hpp
#define Deck_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <random>
#include "Card.hpp"

class Deck{
public:
    Deck(SDL_Renderer*);
    void setDeckOfCards(std::vector<Card>);
    std::vector<Card>& getDeckOfCards();
    void setPlayingDeckOfCards(std::vector<Card>);
    std::vector<Card>& getPlayingDeckOfCards();
    void setBackCards(std::vector<Card>);
    std::vector<Card>& getBackCards();

    int generateRandomNumber();
    void startGame(int); // принтене на картите
    void shuffleDeck(); // размешване
    void printDeck(); // принтиране на тестето
    void printBackCards(); // принтиране задната страна на картите
    void printHintDeck(); // принтираме жокер тестето
    
    void clean();
    
private:
    SDL_Renderer* renderer = NULL;
    SDL_Rect imageDeckRect;
    std::vector<Card> deckOfCards;// тесте от карти
    std::vector<Card> playingDeckOfCards;
    std::vector<Card> backCards;
};

#endif /* Deck_hpp */
