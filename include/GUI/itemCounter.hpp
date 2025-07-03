#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <array>

#include "tiles.hpp"
#include "../structs.hpp"
#include "../constants.hpp"


namespace GUI{
    class ItemCounter{
        SDL_Renderer* m_Renderer;
        std::array<Tiles*, COLOURS> item_count_tiles;
        std::array<SDL_Surface*, COLOURS> surfaces;
        std::array<SDL_Texture*, COLOURS> messages;

        TTF_Font* m_Font;
        SDL_Colour m_Txt_Colour;

        int tile_size;

        public:
            ItemCounter(SDL_Renderer* p_Renderer, TTF_Font* p_font, SDL_Colour p_txt_colour,
                int p_tile_size, std::array<const char*, COLOURS> item_paths);
            ~ItemCounter();
            void draw_tiles();
            void draw_text(std::array<int, COLOURS> item_count);
            void free_text();
    };
}