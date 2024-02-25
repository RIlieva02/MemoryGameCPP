//
//  main.cpp
//  MemoryGame
//
//  Created by Ralitsa Toneva on 20.02.24.
//

#include <iostream>
#include "Game.hpp"
#include "StatisticWindow.hpp"

Game* game = NULL;
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 900;

int main(int argc, char* argv[]) {
    
    pugi::xml_document doc;

    game = new Game();
    game->init("MEMORY GAME",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE);
    game->ttf_init();
    Uint32 startTime = SDL_GetTicks(); // стартираме времето
    while (game->isRunning()) {
        
        game->handleEvents();
        game->render();
    
        float totalTimeSeconds = (SDL_GetTicks() - startTime) / 1000.0f; // превръщаме в секунди
        game->setTime(totalTimeSeconds); // сетваме в класа Game
    }
    
    // Получаване на кореновия елемент
    pugi::xml_node root = doc.first_child();
    
    std::string playerName = game->getPlayerName();
    int moves = game->getMoves();
    int mistakes = game->getMistakes();
    int gameSize = game->getRandomNumber();
    bool result = game->getResult();
    
    // Добавяне на нов елемент с информацията
    pugi::xml_node newPlayer = root.append_child("Player");
    newPlayer.append_attribute("Name").set_value(playerName.c_str());
    newPlayer.append_attribute("Moves").set_value(moves);
    newPlayer.append_attribute("Mistakes").set_value(mistakes);
    newPlayer.append_attribute("GameSize").set_value(gameSize);
    newPlayer.append_attribute("Result").set_value(result);

    // Запис на обновения XML файл
    if (doc.save_file("/Users/ralitsatoneva/Documents/MemoryGameCPP/MemoryGame/MemoryGame/records.xml")) {
        std::cout << "XML файлът е успешно актуализиран." << std::endl;
    } else {
        std::cout << "Грешка при записа на XML файла." << std::endl;
        return 1;
    }
    
    delete game;
    
    return 0;
}
