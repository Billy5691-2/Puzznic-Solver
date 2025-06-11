#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include "../include/structs.hpp"
#include "../include/constants.hpp"

namespace GUI {
    class Board{
        SDL_Renderer* m_Renderer;
        int tile_size = 75;
        int m_board_size;

        public:
            Board(int board_size, SDL_Renderer* p_Renderer);
            void drawBoard();
            int getTileSize();
        
    };
} 
