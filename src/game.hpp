#include <iostream>
#include <fstream>
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

class Game {
    int height;
    int width;
    items items_remaining;
    items items_destroyed;
    std::vector<platform> platforms;
    tiles board[BOARD_SIZE][BOARD_SIZE];




    public:
        Game(std::string level);
        ~Game();
        tiles get_board();
        tiles copy_board();

};