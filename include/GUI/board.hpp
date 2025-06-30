#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include "../structs.hpp"
#include "../constants.hpp"

namespace GUI {
    class Board{
        SDL_Renderer* m_Renderer;
        int tile_size = 75;
        int m_board_size;

        public:
            Board(SDL_Renderer* p_Renderer);
            void drawBoard();
            int getTileSize();
        
    };
} 
