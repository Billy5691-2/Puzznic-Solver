#pragma once
#include <SDL2/SDL.h>
#include "textureManager.hpp"

namespace  GUI {
    class Tiles {
        SDL_Renderer* m_Renderer;
        SDL_Rect* m_TileProperty;
        SDL_Texture* m_TileTexture;
        void init();

        public:
            Tiles(SDL_Renderer* p_Renderer, const char* p_FilePath, int p_TileSize);
            ~Tiles();
            void setPosition(int p_X, int p_Y);
            void draw();

    };
}