#include "include/tile_highlight.hpp"
#include <iostream>
#include "include/gui_data.hpp"
#include "include/rectangle.hpp"
#include "structs.hpp"

GUI::TileHighlight::TileHighlight() {
    std::cout << "TileHighlight: default" << std::endl;
}

GUI::TileHighlight::TileHighlight(const std::shared_ptr<RenderData_t>& renderData)
    : renderData_(renderData), rect_(renderData_, 0, 0, 0, 0) {
    std::cout << "TileHighlight: main" << std::endl;
}

void GUI::TileHighlight::Draw() {
    const Item& item = renderData_->data->GetMoveHighlight();
    if (!item.deleted) {
        rect_.SetPosition(item.position);
        rect_.Draw(HighlightColour);
    }
}