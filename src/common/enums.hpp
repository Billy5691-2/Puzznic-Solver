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
    EXTERIOR,
    INTERIOR,
    FLOOR,
    LEDGE,
    NUMBER_OF_WALL_TYPES,
    WALL_NONE,
};

// enum PlatformPlane_t { HORIZONTAL, VERTICAL };

// enum PlatformDirection_t { POSITIVE = 1, NEGATIVE = -1 };

enum PlatformType {
    UP = 1,
    DOWN = -1,
    LEFT = 2,
    RIGHT = -2,
    NUMBER_OF_PLATFORM_TYPES = 4,
    PLATFORM_NONE = 0,
};

enum OtherType {
    UP_ARROW,
    DOWN_ARROW,
    MOVE_MARKER,
    NUMBER_OF_OTHER_TYPES,
    OTHER_NONE
};

#endif /* E2477351_6198_43E6_8727_1C2B7C9C09BF */
