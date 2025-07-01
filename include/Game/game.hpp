#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <map>
#include "../structs.hpp"
#include "../constants.hpp"
#include "boardState.hpp"

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
        BoardState active_board;

        public:
            Game(std::string level);
            Game(BoardState new_board_state);
            ~Game();
            //board copy_board();

            std::array<int, COLOURS> get_item_count();
            board get_board();
            std::map<position, int> get_item_list();
            std::vector<platform> get_platform_list();

    };
}