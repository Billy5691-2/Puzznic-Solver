#include "include/board_buttons.hpp"
#include <bits/c++config.h>
#include <memory>
#include <vector>
#include "constants.hpp"
#include "include/gui_data.hpp"
#include "structs.hpp"

void GUI::BoardButtons::CheckClicked(const std::shared_ptr<RenderData_t>& renderData, const Coord_t& pixelPos) {
    Coord_t gridPos = ConvertToGrid(pixelPos);
    if (CheckItemsClicked(renderData, gridPos)) {
        return;
    }
    if (CheckMovesClicked(renderData, gridPos)) {
        return;
    }
}

Coord_t GUI::BoardButtons::ConvertToGrid(const Coord_t& pixelPos) {
    Coord_t gridPos;
    gridPos.x = (pixelPos.x - WINDOW_LEFT) / TILE_SIZE;
    gridPos.y = pixelPos.y / TILE_SIZE;
    return gridPos;
}

Coord_t GUI::BoardButtons::ConvertToPixel(const Coord_t& gridPos) {
    Coord_t pixelPos;
    pixelPos.x = (gridPos.x * TILE_SIZE) + WINDOW_LEFT;
    pixelPos.y = gridPos.y * TILE_SIZE;
    return pixelPos;
}

bool GUI::BoardButtons::CheckItemsClicked(const std::shared_ptr<RenderData_t>& renderData, const Coord_t& gridPos) {
    const std::vector<Item_t>& items = renderData->data->GetItems();
    for (std::size_t i = 0; i < items.size(); ++i) {
        if (items[i].position == gridPos) {
            renderData->data->SetMoveItem(i);
            return true;
        }
    }
    return false;
}

bool GUI::BoardButtons::CheckMovesClicked(const std::shared_ptr<RenderData_t>& renderData, const Coord_t& gridPos) {
    const std::vector<Coord_t>& moves = renderData->data->GetMoves();
    for (const auto& move : moves) {
        if (move == gridPos) {
            renderData->data->SetMovePos(gridPos);
            return true;
        }
    }
    return false;
}