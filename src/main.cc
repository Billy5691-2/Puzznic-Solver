#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include "game/include/game.hpp"
#include "gui/include/game_window.hpp"
#include "gui/include/gui_data.hpp"
#include "structs.hpp"

void UpdateGuiData(Puzznic::Game& game, GUI::GuiData& guiData) {
    guiData.SetItemCount(game.GetItemsCount());
    guiData.SetBoard(game.GetBoard());
    guiData.SetAvailableMoves(game.GetAvailableMoves(NO_ITEM_SELECTED));
}

int main() {
    // Initialisation
    GUI::GuiData guiData;
    Puzznic::Game game(guiData.GetLevelPath());

    UpdateGuiData(game, guiData);
    std::unique_ptr<GUI::GuiData> guiDataPtr = std::unique_ptr<GUI::GuiData>(&guiData);
    GUI::GameWindow guiWindow = GUI::GameWindow(guiDataPtr);

    while (guiWindow.GetRunning()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        if (guiData.GetChangeLevelState()) {
            game = Puzznic::Game(guiData.GetLevelPath());
        } else if (guiData.GetSolverStartState()) {
            // Start solver
        } else {
            GUI::GuiDataMutex.lock();
            GUI::GuiMove_t move = guiData.GetMove();
            if (move.moveMade) {
                // Send to Game
                guiData.ResetMove();
            }
            GUI::GuiDataMutex.unlock();
        }
        GUI::GuiDataMutex.lock();
        UpdateGuiData(game, guiData);
        GUI::GuiDataMutex.unlock();
    }

    return 0;
}
