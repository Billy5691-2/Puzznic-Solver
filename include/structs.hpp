#pragma once
#include <vector>

enum platform_plane {
    HORIZONTAL,
    VERTICAL
};

enum platform_direction {
    POSITIVE = 1,
    NEGATIVE = -1
};

enum item_colour {
    RED,
    BLUE,
    GREEN,
    PINK,
    PUPRLE,
    YELLOW,
    CYAN,
    ORANGE
    
};

struct items{
    int red = 0;
    int blue = 0;
    int green = 0;
    int pink = 0;
    int purple = 0;
    int yellow = 0;
    int cyan = 0;
    int orange = 0;
    int total = 0;
};

struct position {
    int x;
    int y;
};

struct item {
    enum item_colour colour;
    position pos;
};

struct tiles {
    int wall = 0;
    int item = 0;
    int platform = 0;
    int empty = 0;
};

struct board {
    int height;
    int width;
    tiles board[20][20];
};

struct platform {
    enum platform_plane plane = HORIZONTAL;
    enum platform_direction direction = POSITIVE;
    position pos;
    std::vector<item> items; 
};