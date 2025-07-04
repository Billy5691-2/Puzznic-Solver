#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <map>

#include "tiles.hpp"
#include "board.hpp"
#include "itemCounter.hpp"
#include "controls.hpp"
//#include <stdlib.h>
#include "../structs.hpp"
#include "../constants.hpp"
#include "../texture_paths.hpp"


// Platform output is untested

namespace GUI {
    class Window {
        SDL_Event* m_Event;
        SDL_Renderer* m_Renderer;
        SDL_Window* m_Window;

        int tile_size;

        bool m_Running = false;

        bool level_change = false;
        bool solve_change = false;
        bool move_change = false;

        ItemCounter* m_Count;
        Board* m_Board;
        Controls* m_Controls;

        std::vector<Tiles*> base_tiles;
        std::vector<Tiles*> platform_tiles;
        std::vector<Tiles*> item_tiles;
        std::vector<Tiles*> item_count_tiles;
        std::vector<Tiles*> move_tiles;

        bool highlight_change;
        move move_pair;

        TTF_Font* m_Font;
        SDL_Colour m_Txt_Colour;

        void init();
        void drawBoard();
        void reset_board(board board_data);
        void reset_platform(std::vector<platform> platform_list);
        void reset_items(std::map<position, int> item_list);

        void reset_moves(std::vector<position> move_list);

        void delete_platforms();
        void delete_board();
        void delete_items();

        void delete_moves();

        void render_board();
        void render_platforms(std::vector<platform> platform_list);
        void render_items(std::map<position, int> item_list);
        
        void render_moves(std::vector<position> move_list);

        position grid_to_pixel(position pos);
        position grid_to_pixel(int x, int y);

        void draw_highlight();

        public:
            Window(const char* title, board board_data, std::vector<platform> platform_list);
            ~Window();

            bool isRunning() const;
            void pollEvent();
            bool update();
            void render(std::map<position, int> item_list, std::vector<platform> platform_list, 
                std::array<int, COLOURS> item_count, std::vector<position> move_list);

            void reset(board board_data, std::vector<platform> platform_list);
            
            std::string new_level_file();
            move get_move();

            bool change_level_state();
            bool start_solver_state();
            bool get_highlight_change();

                
        };
}