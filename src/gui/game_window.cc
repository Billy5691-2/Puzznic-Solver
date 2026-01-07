#include "include/game_window.hpp"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <thread>

#include "SDL2/SDL_events.h"
#include "SDL2/SDL_mouse.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_video.h"
#include "file_paths.hpp"
#include "include/board.hpp"
#include "include/controls.hpp"
#include "include/gui_data.hpp"
#include "include/item_counter.hpp"
#include "include/texture_manager.hpp"

struct SDLWindowDeleter {
    void operator()(SDL_Window* window) const {
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
};

GUI::GameWindow::GameWindow(std::unique_ptr<GuiData>& guiData) : renderData_(std::make_shared<RenderData_t>()) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();

    window_ = windowPtr(SDL_CreateWindow("Puzznic Solver", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                         WINDOW_HEIGHT, SDL_WINDOW_SHOWN));

    // Initialise shared render data struct
    renderData_->data = std::move(guiData);
    renderData_->renderer = std::shared_ptr<SDL_Renderer>(
        SDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_PRESENTVSYNC), SDL_DestroyRenderer);
    renderData_->textures = TextureManager(renderData_->renderer, renderData_->data->GetBasePath());
    std::string fontPath = renderData_->data->GetBasePath() + OPEN_SANS_PATH;
    renderData_->font = fontPtr(TTF_OpenFont(fontPath.c_str(), 30));
    eventHandler_ = std::unique_ptr<SDL_Event>(new SDL_Event);

    board_ = Board(renderData_);
    controls_ = Controls(renderData_);
    itemCounter_ = ItemCounter(renderData_);

    std::thread eventThread(&GameWindow::EventLoop, this);
    eventThread.detach();
    std::thread renderThread(&GameWindow::RenderLoop, this);
    renderThread.detach();
}

void GUI::GameWindow::Render() {
    GuiDataMutex.lock();
    board_.Draw();
    controls_.Draw();
    itemCounter_.Draw();
    GuiDataMutex.unlock();
    SDL_RenderPresent(renderData_->renderer.get());
}

void GUI::GameWindow::InitialiseNewBoard() {
    board_ = Board(renderData_);
}

void GUI::GameWindow::EventLoop() {
    std::cout << "GameWindow: Event thread started\n";
    while (isRunning_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(3)); // Short sleep to reduce CPU usage
        // Handle key presses etc
        if (SDL_PollEvent(eventHandler_.get())) {
            switch (eventHandler_->type) {
                case (SDL_QUIT): {
                    isRunning_ = false;
                }
                case (SDL_MOUSEBUTTONDOWN): {
                    switch (eventHandler_->button.button) {
                        case (SDL_BUTTON_LEFT): {
                            int x = 0, y = 0;
                            SDL_GetMouseState(&x, &y);
                            controls_.CheckClicked({x, y});
                        }
                    }
                }
            }
        }
    }
    std::cout << "GameWindow: Event thread ended\n";
}

void GUI::GameWindow::RenderLoop() {
    std::cout << "GameWindow: Render thread started\n";
    while (isRunning_) {
        // If the board has been changed or reset, initialise the new board and skip this loop
        if (renderData_->data->GetResetBoard()) {
            InitialiseNewBoard();
            Render();
            continue;
        }
        // Render the board
        Render();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    std::cout << "GameWindow: Render thread ended\n";

    SDL_DestroyRenderer(renderData_->renderer.get());
    SDL_DestroyWindow(window_.get());
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool GUI::GameWindow::GetRunning() {
    return isRunning_;
}