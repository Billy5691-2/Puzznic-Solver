#include "include/text.hpp"
#include <iostream>
#include <memory>
#include <string>
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"
#include "SDL2/SDL_ttf.h"
#include "include/gui_data.hpp"

GUI::Text::Text() {
}

GUI::Text::Text(const std::shared_ptr<RenderData_t>& renderData, int x, int y, const std::string& messageStr,
                bool centered)
    : renderData_(renderData), x_(x), y_(y), centered_(centered) {
    if (renderData_ == nullptr) {
        std::cout << "Text: Got nullptr" << std::endl;
        return;
    }

    UpdateText(messageStr);
}

void GUI::Text::UpdateText(int newValue) {
    UpdateText(std::to_string(newValue));
}

void GUI::Text::UpdateText(const std::string& newMessage) {
    char const* message = newMessage.c_str();
    surface_ = SurfacePtr(TTF_RenderText_Solid(renderData_->font.get(), message, TXT_COL));
    texture_ = TexturePtr(SDL_CreateTextureFromSurface(renderData_->renderer.get(), surface_.get()));
    TTF_SizeText(renderData_->font.get(), message, &rect_.w, &rect_.h);
    if (centered_) {
        rect_.x = x_ - (rect_.w / 2);
        rect_.y = y_ - (rect_.h / 2);
    } else {
        rect_.x = x_;
        rect_.y = y_;
    }
}

void GUI::Text::Draw() {
    SDL_RenderCopy(renderData_->renderer.get(), texture_.get(), NULL, &rect_);
}