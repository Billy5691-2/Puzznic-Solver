#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include "board.hpp"
//#include <stdlib.h>
#include "structs.hpp"
#include "constants.hpp"
#include "tiles.hpp"

namespace GUI {
    class Window {
        SDL_Event* m_Event;
        SDL_Renderer* m_Renderer;
        SDL_Window* m_Window;

        bool m_Running = false;
        bool m_Is_Selected = false;

        Board* m_Board;
        Tiles* m_Tile;

        void init();
        void drawBoard();

        public:
            Window(const char* title, int board_size);
            ~Window();

            bool isRunning() const;
            void pollEvent();
            void update();
            void render();

    };
}