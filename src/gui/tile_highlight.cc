#include "tile_highlight.hpp"

#include <iostream>

#include "SDL_render.h"
#include "board_buttons.hpp"
#include "constants.hpp"
#include "gui_data.hpp"
#include "rectangle.hpp"
#include "structs.hpp"

GUI::TileHighlight::TileHighlight() {
}

GUI::TileHighlight::TileHighlight(const std::shared_ptr<RenderData_t>& renderData) : renderData_(renderData) {
    rect_.h = TILE_SIZE;
    rect_.w = TILE_SIZE;
}

void GUI::TileHighlight::Draw() {
    const Item_t& item = renderData_->data->GetMoveHighlight();
    if (!item.deleted) {
        Coord_t rectPosition = BoardButtons::ConvertToPixel(item.position);
        rect_.x = rectPosition.x;
        rect_.y = rectPosition.y;
        SDL_SetRenderDrawColor(renderData_->renderer.get(), HighlightColour.r, HighlightColour.g, HighlightColour.b,
                               HighlightColour.a);
        SDL_RenderDrawRect(renderData_->renderer.get(), &rect_);
        SDL_Rect smallerRect = rect_;
        smallerRect.x += 1;
        smallerRect.y += 1;
        smallerRect.w -= 2;
        smallerRect.h -= 2;
        SDL_RenderDrawRect(renderData_->renderer.get(), &smallerRect);
        smallerRect.x += 1;
        smallerRect.y += 1;
        smallerRect.w -= 2;
        smallerRect.h -= 2;
        SDL_RenderDrawRect(renderData_->renderer.get(), &smallerRect);
    }
}