#include "include/board_buttons.hpp"
#include <memory>
#include <vector>
#include "constants.hpp"
#include "include/gui_data.hpp"
#include "structs.hpp"

void GUI::BoardButtons::CheckClicked(const std::shared_ptr<RenderData_t>& renderData, const Coord& pixelPos) {
    Coord gridPos = ConvertToGrid(pixelPos);
    if (CheckItemsClicked(renderData, gridPos)) {
        return;
    }
    if (CheckMovesClicked(renderData, gridPos)) {
        return;
    }
}

Coord GUI::BoardButtons::ConvertToGrid(const Coord& pixelPos) {
    Coord gridPos;
    gridPos.x = (pixelPos.x - WINDOW_LEFT) / TILE_SIZE;
    gridPos.y = pixelPos.y / TILE_SIZE;
    return gridPos;
}

bool GUI::BoardButtons::CheckItemsClicked(const std::shared_ptr<RenderData_t>& renderData, const Coord& gridPos) {
    const std::map<int, Item>& items = renderData->data->GetItems();
    for (const auto& [key, item] : items) {
        if (item.position == gridPos) {
            renderData->data->SetMoveItem(key);
            return true;
        }
    }
    return false;
}

bool GUI::BoardButtons::CheckMovesClicked(const std::shared_ptr<RenderData_t>& renderData, const Coord& gridPos) {
    const std::vector<Coord>& moves = renderData->data->GetMoves();
    for (const auto& move : moves) {
        if (move == gridPos) {
            renderData->data->SetMovePos(gridPos);
            return true;
        }
    }
    return false;
}