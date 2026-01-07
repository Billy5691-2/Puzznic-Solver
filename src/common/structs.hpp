#ifndef BB679D25_7157_4EB3_A143_1265F5343B72
#define BB679D25_7157_4EB3_A143_1265F5343B72
#include <array>
#include <functional>
#include <vector>
#include "constants.hpp"
#include "enums.hpp"

struct GameTile_t {
    TileType_t tile = EMPTY;
    ItemType item = ITEM_NONE;
    WallType wall = WALL_NONE;
    PlatformType platform = PLATFORM_NONE;
};

struct Coord {
    int x = 0;
    int y = 0;

    bool operator==(const Coord& rhs) const {
        return (x == rhs.x and y == rhs.y);
    }

    bool operator<(const Coord& rhs) const {
        if (x < rhs.x || (x == rhs.x && y < rhs.y)) {
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

struct Move_t {
    int itemID = 0;
    Coord newPos = {0, 0};
};

struct Tile_t {
    int wall = 0;
    int item = 0;
    int platform = 0;
    int empty = 0;
};

struct Platform {
    enum PlatformType direction = PLATFORM_NONE;
    // enum PlatformPlane_t plane = HORIZONTAL;
    // enum PlatformDirection_t direction = POSITIVE;
    Coord pos;
};

struct Item {
    ItemType type = ITEM_NONE;
    Coord position;
    bool deleted = false;
};

// using BoardArr = std::array<std::array<Tile_t, BOARD_SIZE>, BOARD_SIZE>;

// struct BoardHasher {
//     size_t operator()(const BoardArr& board) const {
//         size_t hash = 0;
//         std::hash<int> hasher;

//         for (const auto& row : board) {
//             for (const auto& col : row) {
//                 hash ^= hasher(col.empty) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
//                 hash ^= hasher(col.item) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
//                 hash ^= hasher(col.platform) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
//                 hash ^= hasher(col.wall) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
//             }
//         }

//         return hash;
//     }
// };

#endif /* BB679D25_7157_4EB3_A143_1265F5343B72 */
