#pragma once
#include <vector>
#include <array>

#include <functional>

using BoardArr = std::array<std::array<Tile, kBoardSize>, kBoardSize>;

enum PlatformPlane {
    HORIZONTAL,
    VERTICAL
};

enum PlatformDirection {
    POSITIVE = 1,
    NEGATIVE = -1
};

enum ItemColour {
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

struct Coord {
    int x = 0;
    int y = 0;

    bool operator==(const Coord& rhs) const {
        return (x == rhs.x and y == rhs.y);
    }

    bool operator<(const Coord& rhs) const {
        if (x < rhs.x){
            return true;
        } else if (x == rhs.x && y < rhs.y){
            return true;
        } else {
            return false;
        }
    }

    Coord operator+(const Coord& rhs) const {
        Coord out;
        out.x = x;
        out.y = y;
        out.x += rhs.x;
        out.y += rhs.y;
        return out;
    }
};

template <>
       struct std::hash<Coord> {
           size_t operator()(const Coord& p) const {
               return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
           }
       };

struct Move {
    Coord original;
    Coord updated;
};

struct Tile {
    int wall = 0;
    int item = 0;
    int platform = 0;
    int empty = 0;
};


struct Platform {
    enum PlatformPlane plane = HORIZONTAL;
    enum PlatformDirection direction = POSITIVE;
    Coord pos;
};

struct Item {
    int colour;
    Coord position;
    bool deleted = false;
};

struct BoardHasher {
    size_t operator()(const BoardArr& board) const {
        size_t hash = 0;
        std::hash<int> hasher;

        for (const auto& row : board) {
            for (const auto& col : row) {
                hash ^= hasher(col.empty) + 0x9e3779b9 + (hash << 6) + (hash >> 2); 
                hash ^= hasher(col.item) + 0x9e3779b9 + (hash << 6) + (hash >> 2); 
                hash ^= hasher(col.platform) + 0x9e3779b9 + (hash << 6) + (hash >> 2); 
                hash ^= hasher(col.wall) + 0x9e3779b9 + (hash << 6) + (hash >> 2); 
            }
        }

        return hash;
    }
};