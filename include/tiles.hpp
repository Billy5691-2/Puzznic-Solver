#pragma once
#include <SDL2/SDL.h>
#include "textureManager.hpp"

#define ITEMS_PATH "../assets/items/"
#define PLATFORM_PATH "../assets/platforms/"
#define WALL_PATH "../assets/walls/"

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



namespace  GUI {
    class Tiles {
        SDL_Renderer* m_Renderer;
        SDL_Rect* m_TileProperty;
        SDL_Texture* m_TileTexture;
        void init();

        public:
            Tiles(SDL_Renderer* p_Renderer, const char* p_FilePath, int p_TileSize);
            ~Tiles();
            void setPosition(int p_X, int p_Y);
            void draw();

    };
}