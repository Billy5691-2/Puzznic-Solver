#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <map>
#include "../include/structs.hpp"
#include "../include/constants.hpp"

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

namespace Puzznic {
    class Game {
        board game_board;
        items items_remaining;
        items items_destroyed;
        std::map<int, item_pos> items_list;
        std::map<int, platform> platform_list;
        std::vector<platform> platforms;




        public:
            Game(std::string level);
            ~Game();
            board get_board();
            std::map<int, item_pos>* get_item_list();
            std::map<int, platform>* get_platform_list();
            board copy_board();
            void print_board();

    };
}