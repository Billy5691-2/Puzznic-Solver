#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include "game/include/game.hpp"
#include "gui/include/game_window.hpp"
#include "gui/include/gui_data.hpp"
std::string filename = "levels/level_1_1_cpp.csv";

void const PopulateBoardPointers(Puzznic::Game& game, GUI::GuiData& guiData) {
    guiData.SetItemCountPtr(game.GetItemsCountPtr());
    guiData.SetItemsPtr(game.GetItemsPtr());
    guiData.SetPlatformsPtr(game.GetPlatformsPtr());
    guiData.SetBoardPtr(game.GetBoardPtr());
    guiData.SetAvailableMovesPtr(game.GetAvailableMovesPtr());
}

int main() {
    int level = 0;
    int stage = 0;
    GUI::GuiMove_t move;
    Puzznic::Game game(filename);
    std::cout << "Main: Game object created\n";

    GUI::GuiData guiData;
    guiData.SetMovePtr(std::unique_ptr<GUI::GuiMove_t>(&move));
    guiData.SetLevelPtr(std::unique_ptr<int>(&level));
    guiData.SetStagePtr(std::unique_ptr<int>(&stage));

    PopulateBoardPointers(game, guiData);
    std::cout << "Main: Pointers assigned\n";

    std::unique_ptr<GUI::GuiData> guiDataPtr = std::unique_ptr<GUI::GuiData>(&guiData);

    std::cout << "Main: Unique pointer made" << std::endl;

    GUI::GameWindow guiWindow = GUI::GameWindow(std::move(guiDataPtr));

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
