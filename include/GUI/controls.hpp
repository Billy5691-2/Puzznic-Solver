#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "tiles.hpp"
#include "../texture_paths.hpp"
#include "../constants.hpp"

namespace GUI {
    class Controls{
        SDL_Renderer* m_Renderer;
        TTF_Font* m_Font;
        SDL_Colour m_Txt_Colour;

        Tiles* up_arrow_lvl;
        Tiles* down_arrow_lvl;
        Tiles* up_arrow_stage;
        Tiles* down_arrow_stage;

        SDL_Surface* load_surface;
        SDL_Texture* load_texture;
        SDL_Rect load_rect;

        SDL_Surface* solve_surface;
        SDL_Texture* solve_texture;
        SDL_Rect solve_rect;

        SDL_Surface* level_surface;
        SDL_Texture* level_texture;

        SDL_Surface* stage_surface;
        SDL_Texture* stage_texture;

        int tile_size;

        int stage = 1;
        int level = 1;

        bool solve_pressed = false;
        bool load_pressed = false;



        void draw_load();
        void draw_solve();
        void draw_text();
        void draw_controls();

        void render_buttons();
        void render_text();

        public:
            Controls(SDL_Renderer* p_Renderer, TTF_Font* p_Font, SDL_Colour p_Txt_Colour,
                int p_tile_size);
            ~Controls();

            void render();
            void free();
            
            void check_buttons(int x, int y);

            bool start_solver();
            void set_solver_state();
            
            bool change_level();
            const char* new_level_file();
    };
}