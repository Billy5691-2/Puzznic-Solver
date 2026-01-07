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

struct Coord_t {
    int x = 0;
    int y = 0;

    bool operator==(const Coord_t& rhs) const {
        return (x == rhs.x and y == rhs.y);
    }

    Coord_t operator+(const Coord_t& rhs) const {
        Coord_t out;
        out.x = x;
        out.y = y;
        out.x += rhs.x;
        out.y += rhs.y;
        return out;
    }
};

template <>
struct std::hash<Coord_t> {
    size_t operator()(const Coord_t& p) const {
        return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
    }
};

struct Move_t {
    int itemID = 0;
    Coord_t newPos = {0, 0};
};

struct Tile_t {
    int wall = 0;
    int item = 0;
    int platform = 0;
    int empty = 0;
};

struct Platform_t {
    enum PlatformType direction = PLATFORM_NONE;
    Coord_t pos;
};

struct Item_t {
    ItemType type = ITEM_NONE;
    Coord_t position;
    bool deleted = false;
};

struct Board_t {
    std::vector<Item_t> items;
    std::vector<Platform_t> platforms;
    std::array<std::array<WallType, BOARD_SIZE>, BOARD_SIZE> walls = {};
    int timeUnits = 0;
    std::vector<Move_t> movesMade;

    // Hash based only on items & platforms
    // Equivalence based on items & platforms
    // Potentially ignore the direction a platform is facing - needs some thought
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
