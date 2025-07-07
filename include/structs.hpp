#pragma once
#include <vector>
#include <array>

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
    PURPLE,
    CYAN,
    BROWN,
    ORANGE,
    YELLOW,
    
};

struct position {
    int x = 0;
    int y = 0;

    bool operator==(const position& rhs) const {
        return (x == rhs.x and y == rhs.y);
    }

    bool operator<(const position& rhs) const {
        if (x < rhs.x){
            return true;
        } else if (x == rhs.x && y < rhs.y){
            return true;
        } else {
            return false;
        }
    }

    position operator+(const position& rhs) const {
        position out;
        out.x = x;
        out.y = y;
        out.x += rhs.x;
        out.y += rhs.y;
        return out;
    }
};

struct move {
    position original;
    position updated;
};

struct state {
    bool won;
    bool lose;
};

struct tile {
    int wall = 0;
    int item = 0;
    int platform = 0;
    int empty = 0;
};

struct board {
    int size;
    //tile board[20][20];
    std::array<std::array<tile, 20>, 20> board;
};

struct platform {
    enum platform_plane plane = HORIZONTAL;
    enum platform_direction direction = POSITIVE;
    position pos;
};