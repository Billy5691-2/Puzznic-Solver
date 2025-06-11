#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <map>

#include "tiles.hpp"
#include "board.hpp"
//#include <stdlib.h>
#include "../include/structs.hpp"
#include "../include/constants.hpp"


namespace GUI {
    class Window {
        SDL_Event* m_Event;
        SDL_Renderer* m_Renderer;
        SDL_Window* m_Window;

        bool m_Running = false;
        bool m_Is_Selected = false;

        Board* m_Board;
        Tiles* m_Tile;

        std::map<int, item_pos>* item_list; 

        std::map<int, Tiles*> item_textures;
        std::map<int, Tiles*> platform_textures;

        void init();
        void drawBoard();
        void updateItemList(std::map<int, item_pos>* new_item_list);

        public:
            Window(const char* title, int board_size);
            ~Window();

            bool isRunning() const;
            void pollEvent();
            void update();
            void render();

    };
}