#include "include/game_window.hpp"
#include <iostream>
#include <memory>
#include <thread>

#include "SDL2/SDL_events.h"
#include "SDL2/SDL_mouse.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_video.h"
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

GUI::GameWindow::GameWindow(std::unique_ptr<GuiData> guiData) {
    std::cout << "GameWindow Constructor: Starting Init" << std::endl;
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();

    std::cout << "GameWindow Constructor: Opening Windows" << std::endl;

    // SDL_Window* windowptr = SDL_CreateWindow("Puzznic Solver", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    //                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    window_ = windowPtr(SDL_CreateWindow("Puzznic Solver", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                         WINDOW_HEIGHT, SDL_WINDOW_SHOWN));

    std::cout << "GameWindow Constructor: Window opened" << std::endl;

    renderData_->data = std::move(guiData);
    std::cout << "GameWindow Constructor: 1" << std::endl;
    renderData_->renderer = std::shared_ptr<SDL_Renderer>(
        SDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_PRESENTVSYNC), SDL_DestroyRenderer);
    std::cout << "GameWindow Constructor: 2" << std::endl;
    renderData_->textures = TextureManager(renderData_->renderer);
    std::cout << "GameWindow Constructor: 3" << std::endl;
    eventHandler_ = std::unique_ptr<SDL_Event>(new SDL_Event);

    board_ = Board(renderData_);
    controls_ = Controls(renderData_);
    itemCounter_ = ItemCounter(renderData_);

    std::cout << "GameWindow Constructor: Entering main loop\n";
    isRunning_ = true;
    MainLoop();
    // std::thread guiThread(MainLoop());
    // guiThread.detach();
}

void GUI::GameWindow::Draw() {
    board_.Draw();
    controls_.Draw();
    itemCounter_.Draw();
}

// void GUI::GameWindow::Free() {
//     controls_.Free();
//     itemCounter_.Free();
// }

void GUI::GameWindow::Render() {
    Draw();
    // Free();
    SDL_RenderPresent(renderData_->renderer.get());
}

void GUI::GameWindow::InitialiseNewBoard() {
    board_ = Board(renderData_);
}

bool GUI::GameWindow::MainLoop() {
    while (isRunning_) {
        std::cout << "GameWindow Main Loop\n";
        // If the board has been changed or reset, initialise the new board and skip this loop
        if (renderData_->data->GetResetBoard()) {
            InitialiseNewBoard();
            Render();
            continue;
        }

        // Handle key presses etc
        if (SDL_PollEvent(eventHandler_.get())) {
            switch (eventHandler_->type) {
                case (SDL_QUIT): {
                    isRunning_ = false;
                    break;
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

        // Render the board
        Render();
    }

    SDL_DestroyRenderer(renderData_->renderer.get());
    SDL_DestroyWindow(window_.get());
    SDL_Quit();
    IMG_Quit();
    return true;
}