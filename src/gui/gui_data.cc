#include "include/gui_data.hpp"
#include "constants.hpp"
#include "file_paths.hpp"
#include "structs.hpp"

#include <algorithm>
#include <iostream>
#include <memory>
#include <mutex>
#include <ostream>
#include <string>
#include <utility>

std::mutex GUI::GuiDataMutex;

GUI::GuiData::GuiData() {
    std::string basePath;
    char* sdlPath = SDL_GetBasePath();
    if (sdlPath) {
        basePath = sdlPath;
        SDL_free(sdlPath);
    } else {
        std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
        exit(1);
    }
    size_t pos = basePath.rfind("Puzznic");
    basePath_ = basePath.substr(0, pos) + REPOSITORY_NAME;

    std::cout << "GuiData: Base path" << basePath_ << "\n";
}

/* #################### Game Data Setters ####################### */
void GUI::GuiData::SetItemCount(const std::array<int, NUMBER_OF_ITEMS>& itemCount) {
    itemCount_ = itemCount;
}
void GUI::GuiData::SetBoard(const Board_t& board) {
    board_ = board;
}
void GUI::GuiData::SetAvailableMoves(const std::vector<Coord_t>& moves) {
    availableMoves_ = moves;
}

/* #################### Value Setters ####################### */
void GUI::GuiData::UpdateStage(int change) {
    GuiDataMutex.lock();
    level_.stage += change;
    if (level_.stage > MAX_LEVEL_VALUE) {
        level_.stage = MIN_LEVEL_VALUE;
    } else if (level_.stage < MIN_LEVEL_VALUE) {
        level_.stage = MAX_LEVEL_VALUE;
    }
    GuiDataMutex.unlock();
}
void GUI::GuiData::UpdateSubStage(int change) {
    GuiDataMutex.lock();
    level_.subStage += change;
    if (level_.subStage > MAX_LEVEL_VALUE) {
        level_.subStage = MIN_LEVEL_VALUE;
    } else if (level_.subStage < MIN_LEVEL_VALUE) {
        level_.subStage = MAX_LEVEL_VALUE;
    }
    GuiDataMutex.unlock();
}
void GUI::GuiData::SetMovePos(const Coord_t& pos) {
    GuiDataMutex.lock();
    move_.move.newPos = pos;
    move_.moveMade = true;
    GuiDataMutex.unlock();
}
void GUI::GuiData::SetMoveItem(const int id) {
    GuiDataMutex.lock();
    move_.move.itemID = id;
    GuiDataMutex.unlock();
}
void GUI::GuiData::SetResetBoard(bool flag) {
    GuiDataMutex.lock();
    resetBoard_ = flag;
    GuiDataMutex.unlock();
}
void GUI::GuiData::SetChangeLevel(bool state) {
    GuiDataMutex.lock();
    changeLevel_ = state;
    GuiDataMutex.unlock();
}
void GUI::GuiData::SetSolverStart(bool state) {
    GuiDataMutex.lock();
    startSolver_ = state;
    GuiDataMutex.unlock();
}
void GUI::GuiData::ResetMove() {
    move_.moveMade = false;
}

/* #################### Information Getters ####################### */
bool GUI::GuiData::GetResetBoard() {
    return resetBoard_;
}
bool GUI::GuiData::GetChangeLevelState() {
    return changeLevel_;
}
bool GUI::GuiData::GetSolverStartState() {
    return startSolver_;
}
const GUI::Level_t& GUI::GuiData::GetLevel() {
    return level_;
}
const std::string GUI::GuiData::GetLevelPath() {
    std::string stageDirectory = STAGE_PREFIX + std::to_string(level_.stage) + PATH_SEP;
    std::string levelName = LEVEL_PREFIX + std::to_string(level_.stage) + "_" + std::to_string(level_.subStage) + CSV;
    return basePath_ + LEVEL_FOLDER + stageDirectory + levelName;
}
const std::string& GUI::GuiData::GetBasePath() {
    return basePath_;
}
const GUI::GuiMove_t GUI::GuiData::GetMove() {
    return move_;
}

/* #################### Display Getters ####################### */
const std::array<int, NUMBER_OF_ITEMS>& GUI::GuiData::GetItemCount() {
    return itemCount_;
}
const std::vector<Platform_t>& GUI::GuiData::GetPlatforms() {
    return board_.platforms;
}
const std::vector<Item_t>& GUI::GuiData::GetItems() {
    return board_.items;
}
const std::vector<Coord_t>& GUI::GuiData::GetMoves() {
    return availableMoves_;
}
const Item_t& GUI::GuiData::GetMoveHighlight() {
    return board_.items.at(move_.move.itemID);
}
const std::array<std::array<WallType, BOARD_SIZE>, BOARD_SIZE>& GUI::GuiData::GetWalls() {
    return board_.walls;
}