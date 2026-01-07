#include "include/gui_data.hpp"

#include <iostream>
#include <memory>
#include <mutex>

GUI::GuiData::GuiData() {
    std::cout << "GuiData: Main" << std::endl;
}

/* #################### Pointer Setters ####################### */
void GUI::GuiData::SetItemCountPtr(std::unique_ptr<const std::array<int, NUMBER_OF_ITEMS>> itemCount) {
    dataMutex_.lock();
    itemCount_ = std::move(itemCount);
    dataMutex_.unlock();
}
void GUI::GuiData::SetItemsPtr(std::unique_ptr<const std::map<int, Item>> items) {
    dataMutex_.lock();
    items_ = std::move(items);
    dataMutex_.unlock();
}
void GUI::GuiData::SetPlatformsPtr(std::unique_ptr<const std::map<int, Platform>> platforms) {
    dataMutex_.lock();
    platforms_ = std::move(platforms);
    dataMutex_.unlock();
}
void GUI::GuiData::SetBoardPtr(std::unique_ptr<const std::array<std::array<WallType, BOARD_SIZE>, BOARD_SIZE>> walls) {
    dataMutex_.lock();
    walls_ = std::move(walls);
    dataMutex_.unlock();
}
void GUI::GuiData::SetAvailableMovesPtr(std::unique_ptr<const std::vector<Coord>> moves) {
    dataMutex_.lock();
    availableMoves_ = std::move(moves);
    dataMutex_.unlock();
}

void GUI::GuiData::SetMovePtr(std::unique_ptr<GuiMove_t> move) {
    dataMutex_.lock();
    move_ = std::move(move);
    dataMutex_.unlock();
}
void GUI::GuiData::SetLevelPtr(std::unique_ptr<int> level) {
    dataMutex_.lock();
    currLevel_ = std::move(level);
    dataMutex_.unlock();
}
void GUI::GuiData::SetStagePtr(std::unique_ptr<int> stage) {
    dataMutex_.lock();
    currStage_ = std::move(stage);
    dataMutex_.unlock();
}

/* #################### Value Setters ####################### */
void GUI::GuiData::UpdateLevel(int change) {
    dataMutex_.lock();
    newLevel_ += change;
    if (newLevel_ > 9) {
        newLevel_ = 0;
    } else if (newLevel_ < 0) {
        newLevel_ = 9;
    }
    dataMutex_.unlock();
}
void GUI::GuiData::UpdateStage(int change) {
    dataMutex_.lock();
    newStage_ += change;
    if (newStage_ > 9) {
        newStage_ = 0;
    } else if (newStage_ < 0) {
        newStage_ = 9;
    }
    dataMutex_.unlock();
}
void GUI::GuiData::SetNewLevel() {
    dataMutex_.lock();
    (*currLevel_) = newLevel_;
    (*currStage_) = newStage_;
    dataMutex_.unlock();
}
void GUI::GuiData::SetMovePos(const Coord& pos) {
    dataMutex_.lock();
    move_->move.newPos = pos;
    move_->moveMade = true;
    dataMutex_.unlock();
}
void GUI::GuiData::SetMoveItem(const int id) {
    dataMutex_.lock();
    move_->move.itemID = id;
    dataMutex_.unlock();
}
void GUI::GuiData::SetResetBoard(bool flag) {
    dataMutex_.lock();
    resetBoard_ = flag;
    dataMutex_.unlock();
}
void GUI::GuiData::SetChangeLevel(bool state) {
    dataMutex_.lock();
    changeLevel_ = state;
    dataMutex_.unlock();
}

/* #################### Getters ####################### */
bool GUI::GuiData::GetResetBoard() {
    return resetBoard_;
}
bool GUI::GuiData::GetChangeLevelState() {
    return changeLevel_;
}
int GUI::GuiData::GetLevel() {
    return newLevel_;
}
int GUI::GuiData::GetStage() {
    return newStage_;
}
const std::array<int, NUMBER_OF_ITEMS> GUI::GuiData::GetItemCount() {
    return (*itemCount_);
}
const std::map<int, Platform> GUI::GuiData::GetPlatforms() {
    return (*platforms_);
}
const std::map<int, Item> GUI::GuiData::GetItems() {
    return (*items_);
}
const std::vector<Coord> GUI::GuiData::GetMoves() {
    return (*availableMoves_);
}
const Item GUI::GuiData::GetMoveHighlight() {
    return items_->at(move_->move.itemID);
}
const std::array<std::array<WallType, BOARD_SIZE>, BOARD_SIZE> GUI::GuiData::GetWalls() {
    return (*walls_);
}