//
//  Deck.cpp
//  MemoryGame
//
//  Created by Ralitsa Toneva on 21.02.24.
//

#include "Deck.hpp"

Deck::Deck(SDL_Renderer* renderer) : renderer(renderer){
    
    // пълним вектора
    Card card1("bear", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/bear.png"));
    Card card2("cat", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/cat.png"));
    Card card3("cow", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/cow.png"));
    Card card4("crab", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/crab.png"));
    Card card5("crocodile", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/crocodile.png"));
    Card card6("dog", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/dog.png"));
    Card card7("donkey", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/donkey.png"));
    Card card8("elephant", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/elephant.png"));
    Card card9("fish", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/fish.png"));
    Card card10("fox", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/fox.png"));
    Card card11("giraffe", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/giraffe.png"));
    Card card12("goat", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/goat.png"));
    Card card13("hedgehog", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/hedgehog.png"));
    Card card14("hippo", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/hippo.png"));
    Card card15("horse", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/horse.png"));
    Card card16("jellyfish", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/jellyfish.png"));
    Card card17("kangaroo", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/kangaroo.png"));
    Card card18("koala", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/koala.png"));
    Card card19("lion", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/lion.png"));
    Card card20("owl", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/owl.png"));
    Card card21("panda", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/panda.png"));
    Card card22("peacock", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/peacock.png"));
    Card card23("pig", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/pig.png"));
    Card card24("rabbit", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/rabbit.png"));
    Card card25("rooster", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/rooster.png"));
    Card card26("shark", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/shark.png"));
    Card card27("sheep", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/sheep.png"));
    Card card28("skunk", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/skunk.png"));
    Card card29("snake", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/snake.png"));
    Card card30("tiger", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/tiger.png"));
    Card card31("turtle", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/turtle.png"));
    Card card32("zebra", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Animal_png/zebra.png"));
    
    

    deckOfCards.push_back(card1);
    deckOfCards.push_back(card2);
    deckOfCards.push_back(card3);
    deckOfCards.push_back(card4);
    deckOfCards.push_back(card5);
    deckOfCards.push_back(card6);
    deckOfCards.push_back(card7);
    deckOfCards.push_back(card8);
    deckOfCards.push_back(card9);
    deckOfCards.push_back(card10);
    deckOfCards.push_back(card11);
    deckOfCards.push_back(card12);
    deckOfCards.push_back(card13);
    deckOfCards.push_back(card14);
    deckOfCards.push_back(card15);
    deckOfCards.push_back(card16);
    deckOfCards.push_back(card17);
    deckOfCards.push_back(card18);
    deckOfCards.push_back(card19);
    deckOfCards.push_back(card20);
    deckOfCards.push_back(card21);
    deckOfCards.push_back(card22);
    deckOfCards.push_back(card23);
    deckOfCards.push_back(card24);
    deckOfCards.push_back(card25);
    deckOfCards.push_back(card26);
    deckOfCards.push_back(card27);
    deckOfCards.push_back(card28);
    deckOfCards.push_back(card29);
    deckOfCards.push_back(card30);
    deckOfCards.push_back(card31);
    deckOfCards.push_back(card32);
    
}
void Deck::setDeckOfCards(std::vector<Card> deckOfCards){
    this->deckOfCards = deckOfCards;
}
std::vector<Card>& Deck::getDeckOfCards(){
    return this->deckOfCards;
}
void Deck::setPlayingDeckOfCards(std::vector<Card> playingDeckOfCards){
    this->playingDeckOfCards = playingDeckOfCards;
}
std::vector<Card>& Deck::getPlayingDeckOfCards(){
    return playingDeckOfCards;
}
void Deck::setBackCards(std::vector<Card> deckOfCards){
    this->deckOfCards = deckOfCards;
}
std::vector<Card>& Deck::getBackCards(){
    return this->deckOfCards;
}

int Deck::generateRandomNumber() {
    int randomIndex;
    //srand(time(nullptr));

    // Генериране на произволно число от 0 до 2
    int rNumber = rand() % 3;

    // Избор на вариант в зависимост от произволното число
    switch(rNumber) {
        case 0:
            randomIndex = 16;
            break;
        case 1:
            randomIndex = 36;
            break;
        case 2:
            randomIndex = 64;
            break;
        default:
            std::cout << "Невалидно произволно число!" << std::endl;
        }

    return randomIndex;
}
void Deck::startGame(int number) {
    for (int i = 0; i < number / 2; i++){
        playingDeckOfCards.push_back(deckOfCards.at(i));
        playingDeckOfCards.push_back(deckOfCards.at(i));
    }
    Card backCard("backCard", IMG_LoadTexture(renderer, "/Users/ralitsatoneva/Documents/MemoryGame/Background/cardBack.png"));
    for (int i = 0; i < number; i++){
        backCards.push_back(backCard);
    }
}
void Deck::shuffleDeck() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(playingDeckOfCards.begin(), playingDeckOfCards.end(), rng);
}

void Deck::printDeck(){
    int xCordinates = 5;
    int yCordinates = 5;
    int wCordinates = 100;
    int hCordinates = 100;
    int count = 0;
    
    if (playingDeckOfCards.size() == 16){ // 4 x 4
        for (auto it = playingDeckOfCards.begin(); it != playingDeckOfCards.end(); ++it) {
            it->setRect(xCordinates, yCordinates, wCordinates, hCordinates);
            if(it->isHidden() != true){
                it->drawCard(it->getRect().x, it->getRect().y, it->getRect().w, it->getRect().h, renderer);
            }
            count++;
            xCordinates += 105;
            if (count == 4 || count == 8 || count == 12){
                yCordinates += 105;
                xCordinates = 5;
            }
        }
    }
    if (playingDeckOfCards.size() == 36){ // 6 x 6
        for (auto it = playingDeckOfCards.begin(); it != playingDeckOfCards.end(); ++it) {
            it->setRect(xCordinates, yCordinates, wCordinates, hCordinates);
            if(it->isHidden() != true){
                it->drawCard(it->getRect().x, it->getRect().y, it->getRect().w, it->getRect().h, renderer);
            }
            count++;
            xCordinates += 105;
            if (count == 6 || count == 12 || count == 18 || count == 24 || count == 30){
                yCordinates += 105;
                xCordinates = 5;
            }
        }
    }
    if (playingDeckOfCards.size() == 64){ // 8 x 8
        for (auto it = playingDeckOfCards.begin(); it != playingDeckOfCards.end(); ++it) {
            it->setRect(xCordinates, yCordinates, wCordinates, hCordinates);
            if (it->isHidden() != true){
                it->drawCard(it->getRect().x, it->getRect().y, it->getRect().w, it->getRect().h, renderer);
            }
            count++;
            xCordinates += 105;

            if (count == 8 || count == 16 || count == 24 || count == 32 || count == 40 || count == 48 || count == 56){
                yCordinates += 105;
                xCordinates = 5;
            }
        }
    }
}

void Deck::printBackCards(){
    int xCordinates = 5;
    int yCordinates = 5;
    int count = 0;
    
    if (backCards.size() == 16){ // 4 x 4
        for (auto it = backCards.begin(); it != backCards.end(); ++it) {
            it->drawCard(xCordinates, yCordinates, 100, 100, renderer);
            count++;
            xCordinates += 105;
            if (count == 4 || count == 8 || count == 12){
                yCordinates += 105;
                xCordinates = 5;
            }
        }
    }
    if (backCards.size() == 36){ // 6 x 6
        for (auto it = backCards.begin(); it != backCards.end(); ++it) {
            it->drawCard(xCordinates, yCordinates, 100, 100, renderer);
            count++;
            xCordinates += 105;
            if (count == 6 || count == 12 || count == 18 || count == 24 || count == 30){
                yCordinates += 105;
                xCordinates = 5;
            }
        }
    }
    if (backCards.size() == 64){ // 8 x 8
        for (auto it = backCards.begin(); it != backCards.end(); ++it) {
            it->drawCard(xCordinates, yCordinates, 100, 100, renderer);
            count++;
            xCordinates += 105;
            
            if (count == 8 || count == 16 || count == 24 || count == 32 || count == 40 || count == 48 || count == 56){
                yCordinates += 105;
                xCordinates = 5;
            }
        }
    }
    
}

void Deck::printHintDeck(){
    int xCordinates = 5;
    int yCordinates = 5;
    int wCordinates = 100;
    int hCordinates = 100;
    int count = 0;
    
    if (playingDeckOfCards.size() == 16){ // 4 x 4
        for (auto it = playingDeckOfCards.begin(); it != playingDeckOfCards.end(); ++it) {
            it->setRect(xCordinates, yCordinates, wCordinates, hCordinates);
            if(it->isClicked() == true){
                it->drawCard(it->getRect().x, it->getRect().y, it->getRect().w, it->getRect().h, renderer);
            }
            count++;
            xCordinates += 105;
            if (count == 4 || count == 8 || count == 12){
                yCordinates += 105;
                xCordinates = 5;
            }
        }
    }
    if (playingDeckOfCards.size() == 36){ // 6 x 6
        for (auto it = playingDeckOfCards.begin(); it != playingDeckOfCards.end(); ++it) {
            it->setRect(xCordinates, yCordinates, wCordinates, hCordinates);
            if(it->isClicked() == true){
                it->drawCard(it->getRect().x, it->getRect().y, it->getRect().w, it->getRect().h, renderer);
            }
            count++;
            xCordinates += 105;
            if (count == 6 || count == 12 || count == 18 || count == 24 || count == 30){
                yCordinates += 105;
                xCordinates = 5;
            }
        }
    }
    if (playingDeckOfCards.size() == 64){ // 8 x 8
        for (auto it = playingDeckOfCards.begin(); it != playingDeckOfCards.end(); ++it) {
            it->setRect(xCordinates, yCordinates, wCordinates, hCordinates);
            if (it->isClicked() == true){
                it->drawCard(it->getRect().x, it->getRect().y, it->getRect().w, it->getRect().h, renderer);
            }
            count++;
            xCordinates += 105;

            if (count == 8 || count == 16 || count == 24 || count == 32 || count == 40 || count == 48 || count == 56){
                yCordinates += 105;
                xCordinates = 5;
            }
        }
    }
}
void Deck::clean() {
    std::cout << "cleaning deck\n";
    
    SDL_DestroyRenderer(renderer);
}
