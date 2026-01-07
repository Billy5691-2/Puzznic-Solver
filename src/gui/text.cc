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
    std::cout << "Text: Default" << std::endl;
}

GUI::Text::Text(const std::shared_ptr<RenderData_t>& renderData, int x, int y, std::string& messageStr)
    : renderData_(renderData), x_(x), y_(y) {
    std::cout << "Text: Main" << std::endl;
    if (renderData_ == nullptr) {
        return;
    }

    char const* message = messageStr.c_str();

    surface_ = SurfacePtr(TTF_RenderText_Solid(renderData_->font.get(), message, TXT_COL));
    texture_ = TexturePtr(SDL_CreateTextureFromSurface(renderData->renderer.get(), surface_.get()));
    TTF_SizeText(renderData_->font.get(), message, &rect_.w, &rect_.h);
    rect_.x = x - (rect_.w / 2);
    rect_.y = y - (rect_.h / 2);
    std::cout << "Text: Complete" << std::endl;
}

void GUI::Text::UpdateText(int newValue) {
    UpdateText(std::to_string(newValue));
}

void GUI::Text::UpdateText(const std::string& newMessage) {
    char const* message = newMessage.c_str();
    surface_ = SurfacePtr(TTF_RenderText_Solid(renderData_->font.get(), message, TXT_COL));
    texture_ = TexturePtr(SDL_CreateTextureFromSurface(renderData_->renderer.get(), surface_.get()));
    TTF_SizeText(renderData_->font.get(), message, &rect_.w, &rect_.h);
    rect_.x = x_ - (rect_.w / 2);
    rect_.y = y_ - (rect_.h / 2);
}

void GUI::Text::Draw() {
    SDL_RenderCopy(renderData_->renderer.get(), texture_.get(), NULL, &rect_);
}