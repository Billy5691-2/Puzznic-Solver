#pragma once
#include "window.hpp"
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
