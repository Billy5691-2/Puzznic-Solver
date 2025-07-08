#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <map>
//#include <unordered_map>
#include <unordered_set>
#include "../structs.hpp"
#include "../constants.hpp"

/*
Items: ##
1 = red
2 = blue
3 = green
4 = pink
5 = purple
6 = cyan
7 = brown
8 = orange
9 = yellow

*/

namespace Puzznic{
    class BoardState {
        board game_board;
        std::array<int, COLOURS> item_count;
        std::map<position, int> item_list;
        //std::vector<platform> platform_list;
        std::vector<platform> hor_plat_list;
        std::vector<platform> vert_plat_list;
        
        void game_loop(move move);
        void update_horizontal_platforms();
        void update_vertical_platforms();
        void update_items();
        void destroy_items();

        void print_board();
        void print_item_list();

        bool move_tile(position old_pos, position new_pos);
        bool move_item(position old_pos, position new_pos);
        void update_item_count(int colour);

        void set_board_pos(position pos, tile tile);

        public:
            BoardState() : BoardState("../levels/level_1_1_cpp.csv"){}
            BoardState(std::string level);
            BoardState(board temp_game_board, std::array<int, COLOURS> temp_item_count, 
                std::map<position, int> temp_item_list, 
                std::vector<platform> temp_hor_list, std::vector<platform> temp_vert_list) : 
                game_board(temp_game_board), 
                item_count(temp_item_count), item_list(temp_item_list),
                hor_plat_list(temp_hor_list), vert_plat_list(vert_plat_list) {}
            ~BoardState();
            BoardState copy();

            tile get_board_pos(position pos); 
            std::map<position, int> get_item_list(); 
            std::vector<platform> get_platform_list(); 
            std::array<int, COLOURS> get_item_count(); 
            int get_board_size(); 
            board get_board(); 


    };
}