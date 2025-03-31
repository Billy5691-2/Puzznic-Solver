#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "structs.hpp"

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

const int BOARD_SIZE = 20;
namespace Puzznic {
    class Game {
        board game_board;
        items items_remaining;
        items items_destroyed;
        std::vector<platform> platforms;




        public:
            Game(std::string level);
            ~Game();
            board get_board();
            board copy_board();
            void print_board();

    };
}