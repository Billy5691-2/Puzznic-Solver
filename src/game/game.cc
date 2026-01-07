#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#include "constants.hpp"
#include "enums.hpp"
#include "include/game.hpp"

#include <stdlib.h>
#include <map>
#include <string>
#include <vector>

// Requirements:

// Generate list of valid moves for an item
// Generate list of all valid moves

// Check generated list of moves against hash to reduce compute

// Check order of operations:
// Gravity vs destruction
// items on platforms vs destruction

Puzznic::Game::Game(const std::string& level) {
    itemsCount_.fill(0);
    availableMoves_.reserve(50);

    std::string data;

    std::fstream levelData(level);
    if (!levelData.is_open()) {
        std::cout << "Game Constructor: Failed to open file.\n";
    }

    std::getline(levelData, data);

    int x = 0;
    int currItemCount = 0;
    while (std::getline(levelData, data) && x < BOARD_SIZE) {
        int y = 0;
        std::stringstream ss(data);
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            if (y >= BOARD_SIZE) {
                std::cout << "y out of bounds in read file";
            }

            int tile_value = std::stoi(cell);
            GameTile_t temp;
            Coord tempPos = {x, y};

            Platform tempPlatform;
            tempPlatform.pos = tempPos;
            switch (tile_value) {
                    // ITEMS ########################## //
                case 1: { // Red
                    temp.item = RED;
                    temp.tile = ITEM;
                    ++itemsCount_[RED];
                    items_[currItemCount] = {RED, {tempPos}, false};
                    ++currItemCount;
                    break;
                }
                case 2: { // Blue
                    temp.item = BLUE;
                    temp.tile = ITEM;
                    ++itemsCount_[BLUE];
                    items_[currItemCount] = {BLUE, {tempPos}, false};
                    ++currItemCount;
                    break;
                }
                case 3: { // Green
                    temp.item = GREEN;
                    temp.tile = ITEM;
                    ++itemsCount_[GREEN];
                    items_[currItemCount] = {GREEN, {tempPos}, false};
                    ++currItemCount;
                    break;
                }
                case 4: { // Pink
                    temp.item = PINK;
                    temp.tile = ITEM;
                    ++itemsCount_[PINK];
                    items_[currItemCount] = {PINK, {tempPos}, false};
                    ++currItemCount;
                    break;
                }
                case 5: { // Purple
                    temp.item = PURPLE;
                    temp.tile = ITEM;
                    ++itemsCount_[PURPLE];
                    items_[currItemCount] = {PURPLE, {tempPos}, false};
                    ++currItemCount;
                    break;
                }
                case 6: { // Cyan
                    temp.item = CYAN;
                    temp.tile = ITEM;
                    ++itemsCount_[CYAN];
                    items_[currItemCount] = {CYAN, {tempPos}, false};
                    ++currItemCount;
                    break;
                }
                case 7: { // Brown
                    temp.item = BROWN;
                    temp.tile = ITEM;
                    ++itemsCount_[BROWN];
                    items_[currItemCount] = {BROWN, {tempPos}, false};
                    ++currItemCount;
                    break;
                }
                case 8: { // Orange
                    temp.item = ORANGE;
                    temp.tile = ITEM;
                    ++itemsCount_[ORANGE];
                    items_[currItemCount] = {ORANGE, {tempPos}, false};
                    ++currItemCount;
                    break;
                }
                case 9: { // Yellow
                    temp.item = YELLOW;
                    temp.tile = ITEM;
                    ++itemsCount_[YELLOW];
                    items_[currItemCount] = {YELLOW, {tempPos}, false};
                    ++currItemCount;
                    break;
                }

                    // WALLS ########################## //
                case 101: { // Exterior
                    temp.wall = EXTERIOR;
                    temp.tile = WALL;
                    walls_[x][y] = EXTERIOR;
                    break;
                }
                case 102: { // Floor
                    temp.wall = FLOOR;
                    temp.tile = WALL;
                    walls_[x][y] = FLOOR;
                    break;
                }
                case 103: { // Ledge
                    temp.wall = LEDGE;
                    temp.tile = WALL;
                    walls_[x][y] = LEDGE;
                    break;
                }
                case 104: { // Interior
                    temp.wall = INTERIOR;
                    temp.tile = WALL;
                    walls_[x][y] = INTERIOR;
                    break;
                }
                case 105: {
                    std::cout << "Unhandled Wall Type\n";
                    break;
                }

                    // PLATFORMS ########################## //
                case 201: { // Up
                    temp.platform = UP;
                    temp.tile = PLATFORM;
                    tempPlatform.direction = UP;
                    break;
                }
                case 202: { // Down
                    temp.platform = DOWN;
                    temp.tile = PLATFORM;
                    tempPlatform.direction = DOWN;
                    break;
                }
                case 203: { // Right
                    temp.platform = RIGHT;
                    temp.tile = PLATFORM;
                    tempPlatform.direction = RIGHT;
                    break;
                }
                case 204: { // Left
                    temp.platform = LEFT;
                    temp.tile = PLATFORM;
                    tempPlatform.direction = LEFT;
                    break;
                }
                    // EMPTY ############################## //
                case 999: { // Empty
                    temp.tile = EMPTY;
                    break;
                }

                default: {
                    std::cout << "Game Constructor: Error in file read: " << tile_value << "\n";
                }
            }
            board_[x][y] = temp;
            y++;
        }
        x++;
    }
    levelData.close();

#ifdef INIT_DEBUG
    print_board();
    print_item_list();
#endif
}

//     Game::Game(BoardState new_board_state) {
//         std::cout << "TBD\n";
//     }

//     //Game Destructor
//     Game::~Game() {
//         std::cout << "Close Game 2\n";
//     }

//     board Game::copy_board(){
//         std::cout << "TBD\n";

//         board new_board;
//         new_board.size = game_board.size;
//         //new_board.height = game_board.height;
//         //new_board.width = game_board.width;
//         std::copy(&game_board.board[0][0], &game_board.board[0][0]+kBoardSize*kBoardSize,
// &new_board.board[0][0]); return new_board;
//     }


std::unique_ptr<const std::array<int, NUMBER_OF_ITEMS>> Puzznic::Game::GetItemsCountPtr() {
    return std::move(std::unique_ptr<const std::array<int, NUMBER_OF_ITEMS>>(&itemsCount_));
}
std::unique_ptr<const std::map<int, Item>> Puzznic::Game::GetItemsPtr() {
    return std::move(std::unique_ptr<const std::map<int, Item>>(&items_));
}
std::unique_ptr<const std::map<int, Platform>> Puzznic::Game::GetPlatformsPtr() {
    return std::move(std::unique_ptr<const std::map<int, Platform>>(&platforms_));
}
std::unique_ptr<const std::array<std::array<WallType, BOARD_SIZE>, BOARD_SIZE>> Puzznic::Game::GetBoardPtr() {
    return std::move(std::unique_ptr<const std::array<std::array<WallType, BOARD_SIZE>, BOARD_SIZE>>(&walls_));
}
std::unique_ptr<const std::vector<Coord>> Puzznic::Game::GetAvailableMovesPtr() {
    return std::move(std::unique_ptr<const std::vector<Coord>>(&availableMoves_));
}
PlayState_t Puzznic::Game::GetGameState() {
    return playState_;
}
