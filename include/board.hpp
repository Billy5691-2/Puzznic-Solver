#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include "structs.hpp"

namespace GUI {
    class Board{
        SDL_Renderer* m_Renderer;
        int m_height;
        int m_width;
        int tile_size = 75;

        public:
            Board(position board_data, SDL_Renderer* p_Renderer);
            void drawBoard();
        
    };
} 
