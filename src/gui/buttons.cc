#include <cstddef>
#include <functional>
#include <iostream>

#include "SDL_rect.h"
#include "SDL_render.h"

#include "include/button.hpp"

GUI::Button::Button() {
    std::cout << "Button: Default" << std::endl;
}

GUI::Button::Button(int width, int height, int x, int y, const std::function<void()>& effect) : effect_(effect) {
    std::cout << "Button: Main" << std::endl;
    rect_.x = x;
    rect_.y = y;
    rect_.w = width;
    rect_.h = height;
    effect_ = [&] { effect(); };
    std::cout << "Button: Complete" << std::endl;
}

/**
 * @brief Checks if a clicked pixel is within the bounds of this button and
 * activates the button's effect if it is
 * @param[in] coord struct of Coord type containing the pixel clicked
 */
bool GUI::Button::ClickedButton(const Coord& coord) {
    if (coord.x > rect_.x && coord.x < (rect_.x + rect_.w)) {
        if (coord.y > rect_.y && coord.y < (rect_.y + rect_.h)) {
            if (!clicked_) {
                effect_();
            }
            clicked_ = true;
            return true;
        }
    }
    clicked_ = false;
    return false;
}

bool GUI::Button::IsClicked() {
    return clicked_;
}