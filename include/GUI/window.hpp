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
#include "../structs.hpp"
#include "../constants.hpp"


namespace GUI {
    class Window {
        SDL_Event* m_Event;
        SDL_Renderer* m_Renderer;
        SDL_Window* m_Window;

        bool m_Running = false;
        bool m_Is_Selected = false;

        Board* m_Board;
        Tiles* m_Tile;

        std::map<position, int>* item_list; 

        std::map<int, Tiles*> item_textures;
        std::map<int, Tiles*> platform_textures;

        void init();
        void drawBoard();
        void updateItemList(std::map<position, int>* new_item_list);

        public:
            Window(const char* title, int board_size);
            ~Window();

            bool isRunning() const;
            void pollEvent();
            void update();
            void render();

    };
}