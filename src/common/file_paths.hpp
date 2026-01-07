#ifndef F4976560_115A_488E_B794_F6EB31DBE721
#define F4976560_115A_488E_B794_F6EB31DBE721

#include <string>

#ifdef _WIN32
const std::string PATH_SEP = "\\";
#else
const std::string PATH_SEP = "/";
#endif

// Project directory
const std::string REPOSITORY_NAME = "Puzznic-Solver" + PATH_SEP;

// Asset directories
const std::string LEVEL_FOLDER = "levels" + PATH_SEP;
const std::string TEXTURE_FOLDER = "assets" + PATH_SEP;

// Level prefixes
const std::string STAGE_PREFIX = "stage_";
const std::string LEVEL_PREFIX = "level_";
const std::string CSV = "_cpp.csv";
// Format: stage_(stage #)/level_(stage #)_(sub stage #).csv

// Texture sub directories
const std::string ITEMS_SUB_FOLDER = "items" + PATH_SEP;
const std::string ITEMS_PATH = TEXTURE_FOLDER + ITEMS_SUB_FOLDER;

const std::string PLATFORMS_SUB_FOLDER = "platforms" + PATH_SEP;
const std::string PLATFORMS_PATH = TEXTURE_FOLDER + PLATFORMS_SUB_FOLDER;

const std::string WALLS_SUB_FOLDER = "walls" + PATH_SEP;
const std::string WALLS_PATH = TEXTURE_FOLDER + WALLS_SUB_FOLDER;

const std::string MISC_SUB_FOLDER = "misc" + PATH_SEP;
const std::string MISC_PATH = TEXTURE_FOLDER + MISC_SUB_FOLDER;

// Font directories
const std::string FONTS_SUB_FOLDER = "fonts" + PATH_SEP;
const std::string FONTS_PATH = TEXTURE_FOLDER + FONTS_SUB_FOLDER;
const std::string OPEN_SANS_PATH = FONTS_PATH + "OpenSans-Regular.ttf";

// Texture suffixes
const std::string PNG = ".png";
const std::string ITEM_SUFFIX = "_Item" + PNG;
const std::string WALL_SUFFIX = "_Wall" + PNG;
const std::string PLATFORM_SUFFIX = "_Platform" + PNG;

const std::string RED_ITEM_PATH = ITEMS_PATH + "1_Red" + ITEM_SUFFIX;
const std::string BLUE_ITEM_PATH = ITEMS_PATH + "2_Blue" + ITEM_SUFFIX;
const std::string GREEN_ITEM_PATH = ITEMS_PATH + "3_Green" + ITEM_SUFFIX;
const std::string PINK_ITEM_PATH = ITEMS_PATH + "4_Pink" + ITEM_SUFFIX;
const std::string PURPLE_ITEM_PATH = ITEMS_PATH + "5_Purple" + ITEM_SUFFIX;
const std::string CYAN_ITEM_PATH = ITEMS_PATH + "6_Cyan" + ITEM_SUFFIX;
const std::string BROWN_ITEM_PATH = ITEMS_PATH + "7_Brown" + ITEM_SUFFIX;
const std::string ORANGE_ITEM_PATH = ITEMS_PATH + "8_Orange" + ITEM_SUFFIX;
const std::string YELLOW_ITEM_PATH = ITEMS_PATH + "9_Yellow" + ITEM_SUFFIX;

const std::string EXTERIOR_WALL_PATH = WALLS_PATH + "1_Exterior" + WALL_SUFFIX;
const std::string FLOOR_WALL_PATH = WALLS_PATH + "2_Floor" + WALL_SUFFIX;
const std::string LEDGE_WALL_PATH = WALLS_PATH + "3_Ledge" + WALL_SUFFIX;
const std::string INTERIOR_WALL_PATH = WALLS_PATH + "4_Interior" + WALL_SUFFIX;
const std::string GREEN_WALL_PATH = WALLS_PATH + "5_Green" + WALL_SUFFIX;

const std::string UP_PLATFORM_PATH = PLATFORMS_PATH + "1_Up" + PLATFORM_SUFFIX;
const std::string DOWN_PLATFORM_PATH = PLATFORMS_PATH + "2_Down" + PLATFORM_SUFFIX;
const std::string RIGHT_PLATFORM_PATH = PLATFORMS_PATH + "3_Right" + PLATFORM_SUFFIX;
const std::string LEFT_PLATFORM_PATH = PLATFORMS_PATH + "4_Left" + PLATFORM_SUFFIX;

const std::string UP_ARROW_PATH = MISC_PATH + "Up_Arrow" + PNG;
const std::string DOWN_ARROW_PATH = MISC_PATH + "Down_Arrow" + PNG;

const std::string MOVE_MARKER_PATH = MISC_PATH + "Move_Marker" + PNG;

#endif /* F4976560_115A_488E_B794_F6EB31DBE721 */
