
#include "include/rectangle.hpp"
#include <iostream>
#include <memory>
#include "SDL2/SDL_pixels.h"
#include "include/gui_data.hpp"

GUI::Rectangle::Rectangle() : Rectangle(nullptr, 0, 0, 0, 0) {
}

GUI::Rectangle::Rectangle(const std::shared_ptr<RenderData_t>& renderData, int x, int y, int w, int h)
    : renderData_(renderData), rect_({x, y, w, h}) {
}

void GUI::Rectangle::SetPosition(const Coord_t& coord) {
    rect_.x = coord.x;
    rect_.y = coord.y;
}

void GUI::Rectangle::Draw(const SDL_Colour& textColour) {
    // Draw the centre of the rectangle
    SDL_SetRenderDrawColor(renderData_->renderer.get(), textColour.r, textColour.g, textColour.b, textColour.a);
    SDL_RenderFillRect(renderData_->renderer.get(), &rect_);

    // Draw the border of the rectangle
    SDL_SetRenderDrawColor(renderData_->renderer.get(), BRDER_COL.r, BRDER_COL.g, BRDER_COL.b, BRDER_COL.a);
    SDL_RenderDrawRect(renderData_->renderer.get(), &rect_);
}