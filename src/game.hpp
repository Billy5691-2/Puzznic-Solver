#include <iostream>
#include <stdlib.h>

/*
Tiles: ###
0## = Items 
1## = Walls
2## = Moving

Items: ##
000 = red
001 = blue
002 = green
003 = pink
004 = purple
*/

enum platform_plane {
    HORIZONTAL,
    VERTICAL
};

enum platform_direction {
    POSITIVE = 1,
    NEGATIVE = -1
};

struct items{
    int red = 0;
    int blue = 0;
    int green = 0;;
    int pink = 0;
    int purple = 0;
    int yellow = 0;
    int cyan = 0;
    int orange = 0;
};

struct tiles {
    int wall = 0;
    int item = 0;
    int platform = 0;
};

struct platform {
    enum platform_plane plane = HORIZONTAL;
    enum platform_direction direction = POSITIVE;
    int x;
    int y;
};

class Game {
    int height;
    int width;
    tiles[] board;




    public:
        std::string[] get_board();

};