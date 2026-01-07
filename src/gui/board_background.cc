#include "include/board_background.hpp"
#include "../common/constants.hpp"
#include "include/gui_data.hpp"

GUI::BoardBackground::BoardBackground() {
}

GUI::BoardBackground::BoardBackground(const std::shared_ptr<RenderData_t>& renderData) : renderData_(renderData) {
    if (renderData_ == nullptr) {
        std::cout << "BoardBackground: Constructor got nullptr\n";
        return;
    }
}

void GUI::BoardBackground::DrawBackground() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            SDL_Rect _block;
            _block.x = (i * TILE_SIZE) + WINDOW_LEFT;
            _block.y = j * TILE_SIZE;
            _block.w = _block.h = TILE_SIZE;
            SDL_SetRenderDrawColor(renderData_->renderer.get(), 0, 20, 45, 30);
            SDL_RenderFillRect(renderData_->renderer.get(), &_block);

            SDL_SetRenderDrawColor(renderData_->renderer.get(), 0, 0, 0, 255);
            SDL_RenderDrawRect(renderData_->renderer.get(), &_block);
        }
    }
}