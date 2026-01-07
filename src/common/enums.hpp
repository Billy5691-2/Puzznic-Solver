#ifndef E2477351_6198_43E6_8727_1C2B7C9C09BF
#define E2477351_6198_43E6_8727_1C2B7C9C09BF

typedef enum {
    PLAYING,
    WON,
    LOST,
} PlayState_t;

typedef enum {
    ITEM = 0,
    WALL,
    PLATFORM,
    EMPTY
} TileType_t;

enum ItemType {
    RED = 0,
    BLUE,
    GREEN,
    PINK,
    PURPLE,
    CYAN,
    BROWN,
    ORANGE,
    YELLOW,
    NUMBER_OF_ITEMS,
    ITEM_NONE
};

enum WallType {
    EXTERIOR = 0,
    INTERIOR,
    FLOOR,
    LEDGE,
    NUMBER_OF_WALL_TYPES,
    WALL_NONE,
};

enum PlatformType {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    NUMBER_OF_PLATFORM_TYPES,
    PLATFORM_NONE,
};

enum MiscType {
    UP_ARROW = 0,
    DOWN_ARROW,
    MOVE_MARKER,
    NUMBER_OF_MISC_TYPES,
    MISC_NONE
};

#endif /* E2477351_6198_43E6_8727_1C2B7C9C09BF */
