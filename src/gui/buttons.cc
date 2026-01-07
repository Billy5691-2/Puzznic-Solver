#include <chrono>
#include <cstddef>
#include <functional>
#include <iostream>
#include <thread>

#include "SDL_rect.h"
#include "SDL_render.h"

#include "include/button.hpp"

GUI::Button::Button() {
}

GUI::Button::Button(int width, int height, int x, int y, std::function<void()> effect) : effect_(effect) {
    rect_.x = x;
    rect_.y = y;
    rect_.w = width;
    rect_.h = height;
}

/**
 * @brief Checks if a clicked pixel is within the bounds of this button and
 * activates the button's effect if it is
 * @param[in] coord struct of Coord_t type containing the pixel clicked
 */
bool GUI::Button::ClickedButton(const Coord_t& coord) {
    if (coord.x > rect_.x && coord.x < (rect_.x + rect_.w)) {
        if (coord.y > rect_.y && coord.y < (rect_.y + rect_.h)) {
            if (!clicked_) {
                effect_();
                std::thread resetThread(&Button::ResetClicked, this);
                resetThread.detach();
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

void GUI::Button::ResetClicked() {
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    clicked_ = false;
}