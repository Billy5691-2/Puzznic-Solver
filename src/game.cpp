#include <stdlib.h>
#include <math.h>

#include <iostream>
#include <fstream>
#include "game.hpp"

Game::Game(std::string level) {
    std::string data;

    std::fstream levelData(level);

    std::getline (levelData, data);
    height = atoi(data);
    std::getline (levelData, data);
    width = atoi(data);

    while (std::getline (levelData, data)) {

    }
    levelData.close();


}

Game::~Game() {

}