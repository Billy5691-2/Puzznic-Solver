#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <map>
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
        std::vector<platform> platform_list;
        
        //void update_platform_positions();
        void update_item_count(int colour);

        void print_board();
        void print_item_list();

        public:
            BoardState() : BoardState("../levels/level_1_1_cpp.csv"){}
            BoardState(std::string level);
            BoardState(board temp_game_board, std::array<int, COLOURS> temp_item_count, std::map<position, int> temp_item_list, 
                std::vector<platform> temp_platform_list); 
            ~BoardState();
            //BoardState copy_state();
            //std::map<position, int> copy_item_list();
            //std::map<int, platform> copy_platform_list();
            //board copy_board();

            tile get_board_pos(position pos); 
            std::map<position, int> get_item_list(); 
            std::vector<platform> get_platform_list(); 
            std::array<int, COLOURS> get_item_count(); 
            int get_board_size(); 
            board get_board(); 

            //void update_item_list(position item, position new_pos);
            //void remove_item_list(position item);
    };
}