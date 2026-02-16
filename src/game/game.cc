#include <bits/c++config.h>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "constants.hpp"
#include "enums.hpp"
#include "include/game.hpp"
#include "structs.hpp"

// Requirements:

// Generate list of valid moves for an item
// Generate list of all valid moves

// Check generated list of moves against hash to reduce compute

// Check order of operations:
// Gravity vs destruction
// items on platforms vs destruction

Puzznic::Game::Game(const std::string& level) : availableMoves_(std::make_shared<AllMoves_u>()) {
    itemsCount_.fill(0);
    board_.items.reserve(20);
    board_.platforms.reserve(5);

    std::string data;

    std::fstream levelData(level);
    if (!levelData.is_open()) {
        std::cout << "Game Constructor: Failed to open file. Path: " << level << "\n";
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
                std::cout << "y out of bounds while reading file";
            }

            int tileValue = std::stoi(cell);

            board_.walls[x][y] = WALL_NONE;
            switch (tileValue) {
                    // ITEMS ########################## //
                case 1: { // Red
                    ++itemsCount_[RED];
                    board_.items.push_back({
                        RED, {x, y},
                         false
                    });
                    ++currItemCount;
                    break;
                }
                case 2: { // Blue
                    ++itemsCount_[BLUE];
                    board_.items.push_back({
                        BLUE, {x, y},
                         false
                    });
                    ++currItemCount;
                    break;
                }
                case 3: { // Green
                    ++itemsCount_[GREEN];
                    board_.items.push_back({
                        GREEN, {x, y},
                         false
                    });
                    ++currItemCount;
                    break;
                }
                case 4: { // Pink
                    ++itemsCount_[PINK];
                    board_.items.push_back({
                        PINK, {x, y},
                         false
                    });
                    ++currItemCount;
                    break;
                }
                case 5: { // Purple
                    ++itemsCount_[PURPLE];
                    board_.items.push_back({
                        PURPLE, {x, y},
                         false
                    });
                    ++currItemCount;
                    break;
                }
                case 6: { // Cyan
                    ++itemsCount_[CYAN];
                    board_.items.push_back({
                        CYAN, {x, y},
                         false
                    });
                    ++currItemCount;
                    break;
                }
                case 7: { // Brown
                    ++itemsCount_[BROWN];
                    board_.items.push_back({
                        BROWN, {x, y},
                         false
                    });
                    ++currItemCount;
                    break;
                }
                case 8: { // Orange
                    ++itemsCount_[ORANGE];
                    board_.items.push_back({
                        ORANGE, {x, y},
                         false
                    });
                    ++currItemCount;
                    break;
                }
                case 9: { // Yellow
                    ++itemsCount_[YELLOW];
                    board_.items.push_back({
                        YELLOW, {x, y},
                         false
                    });
                    ++currItemCount;
                    break;
                }

                    // WALLS ########################## //
                case 101: { // Exterior
                    board_.walls[x][y] = EXTERIOR;
                    break;
                }
                case 102: { // Floor
                    board_.walls[x][y] = FLOOR;
                    break;
                }
                case 103: { // Ledge
                    board_.walls[x][y] = LEDGE;
                    break;
                }
                case 104: { // Interior
                    board_.walls[x][y] = INTERIOR;
                    break;
                }
                case 105: {
                    std::cout << "Unhandled Wall Type\n";
                    break;
                }

                    // PLATFORMS ########################## //
                case 201: { // Up
                    board_.platforms.push_back({
                        UP, {x, y}
                    });
                    break;
                }
                case 202: { // Down
                    board_.platforms.push_back({
                        DOWN, {x, y}
                    });
                    break;
                }
                case 203: { // Right
                    board_.platforms.push_back({
                        RIGHT, {x, y}
                    });
                    break;
                }
                case 204: { // Left
                    board_.platforms.push_back({
                        LEFT, {x, y}
                    });
                    break;
                }

                case 999: {
                    // Empty tile
                    break;
                }

                default: {
                    std::cout << "Game Constructor: Error in file read: " << tileValue << "\n";
                }
            }
            ++y;
        }
        ++x;
    }
    levelData.close();
    board_.items.shrink_to_fit();
    board_.platforms.shrink_to_fit();
}

bool Puzznic::Game::IsTileEmpty(const Coord_t& pos) {
    if (board_.walls[pos.x][pos.y] != WALL_NONE) {
        return false;
    }
    for (const auto& item : board_.items) {
        if (item.position == pos) {
            return false;
        }
    }
    for (const auto& platform : board_.platforms) {
        if (platform.pos == pos) {
            return false;
        }
    }
    return true;
}

bool inline Puzznic::Game::IsAdjacent(const Coord_t& posOne, const Coord_t& posTwo) {
    return abs(posOne.x - posTwo.x) + abs(posOne.y - posTwo.y) == 1;
}

void Puzznic::Game::UpdateMatches() {
    std::vector<std::size_t> matchedItems;
    matchedItems.reserve(board_.items.size());

    // Find all matched items and add them to a vector
    for (std::size_t index = 0; index < board_.items.size(); ++index) {
        if (IsTileEmpty(board_.items[index].position + DOWN_POS)) {
            // Items do not match if they are falling
            continue;
        }
        for (std::size_t otherIndex = index + 1; otherIndex < board_.items.size(); ++otherIndex) {
            const Item_t& comparisonItem = board_.items[otherIndex];
            const Item_t& item = board_.items[index];
            if (IsTileEmpty(comparisonItem.position + DOWN_POS) ||
                !IsAdjacent(item.position, comparisonItem.position) || item.type != comparisonItem.type) {
                // Items do not match if:
                // - One or both are falling
                // - They are not matching colours
                // - They are not adjacent
                continue;
            }
            matchedItems.push_back(index);
            matchedItems.push_back(otherIndex);
        }
    }
    for (const auto& index : matchedItems) {
        board_.items[index].deleted = true;
        board_.items[index].position = {-1, -1};
    }
}

void Puzznic::Game::CountItems() {
    itemsCount_.fill(0);
    for (const auto& item : board_.items) {
        ++itemsCount_[item.type];
    }
}

void Puzznic::Game::UpdateGameState() {
    CountItems();
    bool itemsRemaining = false;
    for (const auto& count : itemsCount_) {
        if (count) {
            itemsRemaining = true;
        }
        if (count == 1) { // Single items cannot be matched
            playState_ = LOST;
            return;
        }
    }
    if (itemsRemaining) {
        playState_ = PLAYING;
    } else {
        playState_ = WON;
    }
}

void Puzznic::Game::UpdateGravity() {
    for (auto& item : board_.items) {
        if (IsTileEmpty(item.position + DOWN_POS)) {
            item.position += DOWN_POS;
        }
    }
}

// ################################ External Getters
const std::array<int, NUMBER_OF_ITEMS>& Puzznic::Game::GetItemsCount() {
    return itemsCount_;
}
const Board_t& Puzznic::Game::GetBoard() {
    return board_;
}
const std::vector<Coord_t> Puzznic::Game::GetAvailableMoves(const std::size_t itemIndex) {
    if (itemIndex > board_.items.size()) {
        return {};
    }

    MoveChain_u moveChain;
    for (const auto& [destination, path] : (*availableMoves_)[itemIndex]) {
        moveChain.push_back(destination);
    }
    return moveChain;
}
PlayState_t Puzznic::Game::GetGameState() {
    return playState_;
}
