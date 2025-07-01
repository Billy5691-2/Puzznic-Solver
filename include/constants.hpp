#pragma once

const int BOARD_SIZE = 20;

const int COLOURS = 8;

const int WINDOW_HEIGHT = 900;
const int WINDOW_WIDTH = WINDOW_HEIGHT * 1.6;
const int WINDOW_LEFT = (WINDOW_WIDTH - WINDOW_HEIGHT) * 0.4; // Righthand edge of window leftside
const int WINDOW_RIGHT_OFFSET = WINDOW_HEIGHT + WINDOW_LEFT; //Lefthand side of window rightside
const int WINDOW_RIGHT_SIZE = (WINDOW_WIDTH - WINDOW_HEIGHT) * 0.6; //Lefthand side of window rightside

//const int WINDOW_WIDTH = 1200;

#define ITEMS_PATH "../../assets/items/"
#define PLATFORM_PATH "../../assets/platforms/"
#define WALL_PATH "../../assets/walls/"

#define ITEM "_Item.png"
#define WALL "_Wall.png"
#define PLATFORM "_Platform.png"

#define RED_ITEM ITEMS_PATH "1_Red" ITEM
#define BLUE_ITEM ITEMS_PATH "2_Blue" ITEM
#define GREEN_ITEM ITEMS_PATH "3_Green" ITEM
#define PINK_ITEM ITEMS_PATH "4_Pink" ITEM
#define PURPLE_ITEM ITEMS_PATH "5_Purple" ITEM
#define CYAN_ITEM ITEMS_PATH "6_Cyan" ITEM
#define BROWN_ITEM ITEMS_PATH "7_Brown" ITEM
#define ORANGE_ITEM ITEMS_PATH "8_Orange" ITEM
#define YELLOW_ITEM ITEMS_PATH "9_Yellow" ITEM

#define EXTERIOR_WALL WALL_PATH "1_Exterior" WALL
#define FLOOR_WALL WALL_PATH "2_Floor" WALL
#define LEDGE_WALL WALL_PATH "3_Ledge" WALL
#define INTERIOR_WALL WALL_PATH "4_Interior" WALL
#define GREEN_WALL WALL_PATH "5_Green" WALL

#define UP_PLATFORM PLATFORM_PATH "1_Up" PLATFORM
#define DOWN_PLATFORM PLATFORM_PATH "2_Down" PLATFORM
#define RIGHT_PLATFORM PLATFORM_PATH "3_Right" PLATFORM
#define LEFT_PLATFORM PLATFORM_PATH "4_Left" PLATFORM 


/*
const char* ITEMS_PATH = "../../assets/items/";
const char* PLATFORM_PATH  = "../../assets/platforms/";
const char* WALL_PATH = "../../assets/walls/";

const char* ITEM = "_Item.png";
const char* WALL = "_Wall.png";
const char* PLATFORM = "_Platform.png";

const char* RED_ITEM = ITEMS_PATH + "1_Red" + ITEM;
const char* BLUE_ITEM = ITEMS_PATH + "2_Blue" + ITEM;
const char* GREEN_ITEM = ITEMS_PATH + "3_Green" + ITEM;
const char* PINK_ITEM = ITEMS_PATH + "4_Pink" + ITEM;
const char* PURPLE_ITEM = ITEMS_PATH + "5_Purple" + ITEM;
const char* CYAN_ITEM = ITEMS_PATH + "6_Cyan" + ITEM;
const char* BROWN_ITEM = ITEMS_PATH + "7_Brown" + ITEM;
const char* ORANGE_ITEM = ITEMS_PATH + "8_Orange" + ITEM;
const char* YELLOW_ITEM = ITEMS_PATH + "9_Yellow" + ITEM;

const char* EXTERIOR_WALL = WALL_PATH + "1_Exterior" + WALL;
const char* FLOOR_WALL = WALL_PATH + "2_Floor" + WALL;
const char* LEDGE_WALL = WALL_PATH + "3_Ledge" + WALL;
const char* INTERIOR_WALL = WALL_PATH + "4_Interior" + WALL;
const char* GREEN_WALL = WALL_PATH + "5_Green" + WALL;

const char* UP_PLATFORM = PLATFORM_PATH + "1_Up" + PLATFORM;
const char* DOWN_PLATFORM = PLATFORM_PATH + "2_Down" + PLATFORM;
const char* RIGHT_PLATFORM = PLATFORM_PATH + "3_Right" + PLATFORM;
const char* LEFT_PLATFORM = PLATFORM_PATH + "4_Left" + PLATFORM;
*/