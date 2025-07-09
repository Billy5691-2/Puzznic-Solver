#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include "../structs.hpp"
#include "../constants.hpp"

namespace GUI {
    class BoardBackground{
        SDL_Renderer* m_Renderer;
        int tileSize_ = 75;
        int m_board_size;

        public:
            BoardBackground(SDL_Renderer* p_Renderer);
            void DrawBackground();
            int GetTileSize();
        
    };
} 
