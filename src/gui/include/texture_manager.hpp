#ifndef C9926753_4601_4BBC_A18B_95D28733B4E7
#define C9926753_4601_4BBC_A18B_95D28733B4E7

#include <array>
#include "SDL_render.h"
#define ITEMS_PATH    "../assets/items/"
#define PLATFORM_PATH "../assets/platforms/"
#define WALL_PATH     "../assets/walls/"
#define EXTRA_PATH    "../assets/extra/"

#define ITEM_SUFFIX     "_Item.png"
#define WALL_SUFFIX     "_Wall.png"
#define PLATFORM_SUFFIX "_Platform.png"
#define PNG             ".png"

#define RED_ITEM_PATH    ITEMS_PATH "1_Red" ITEM_SUFFIX
#define BLUE_ITEM_PATH   ITEMS_PATH "2_Blue" ITEM_SUFFIX
#define GREEN_ITEM_PATH  ITEMS_PATH "3_Green" ITEM_SUFFIX
#define PINK_ITEM_PATH   ITEMS_PATH "4_Pink" ITEM_SUFFIX
#define PURPLE_ITEM_PATH ITEMS_PATH "5_Purple" ITEM_SUFFIX
#define CYAN_ITEM_PATH   ITEMS_PATH "6_Cyan" ITEM_SUFFIX
#define BROWN_ITEM_PATH  ITEMS_PATH "7_Brown" ITEM_SUFFIX
#define ORANGE_ITEM_PATH ITEMS_PATH "8_Orange" ITEM_SUFFIX
#define YELLOW_ITEM_PATH ITEMS_PATH "9_Yellow" ITEM_SUFFIX

#define EXTERIOR_WALL_PATH WALL_PATH "1_Exterior" WALL_SUFFIX
#define FLOOR_WALL_PATH    WALL_PATH "2_Floor" WALL_SUFFIX
#define LEDGE_WALL_PATH    WALL_PATH "3_Ledge" WALL_SUFFIX
#define INTERIOR_WALL_PATH WALL_PATH "4_Interior" WALL_SUFFIX
#define GREEN_WALL_PATH    WALL_PATH "5_Green" WALL_SUFFIX

#define UP_PLATFORM_PATH    PLATFORM_PATH "1_Up" PLATFORM_SUFFIX
#define DOWN_PLATFORM_PATH  PLATFORM_PATH "2_Down" PLATFORM_SUFFIX
#define RIGHT_PLATFORM_PATH PLATFORM_PATH "3_Right" PLATFORM_SUFFIX
#define LEFT_PLATFORM_PATH  PLATFORM_PATH "4_Left" PLATFORM_SUFFIX

#define UP_ARROW_PATH   EXTRA_PATH "Up_Arrow" PNG
#define DOWN_ARROW_PATH EXTRA_PATH "Down_Arrow" PNG

#define MOVE_MARKER_PATH EXTRA_PATH "Move_Marker" PNG

#include <SDL2/SDL_image.h>
#include <memory>
#include "../../common/enums.hpp"

namespace GUI {

    enum TextureType {
        TEX_ITEM,
        TEX_PLATFORM,
        TEX_WALL,
        TEX_OTHER,
    };

    class TextureManager {
        std::array<std::shared_ptr<SDL_Texture>, NUMBER_OF_ITEMS> itemTextures_;
        std::array<std::shared_ptr<SDL_Texture>, NUMBER_OF_WALL_TYPES> wallTextures_;
        std::array<std::shared_ptr<SDL_Texture>, NUMBER_OF_PLATFORM_TYPES> platformTextures_;
        std::array<std::shared_ptr<SDL_Texture>, NUMBER_OF_OTHER_TYPES> otherTextures_;
        std::shared_ptr<SDL_Renderer> renderHandler_;

        std::shared_ptr<SDL_Texture> GenerateItemTexture(ItemType itemType);
        std::shared_ptr<SDL_Texture> GeneratePlatformTexture(PlatformType platformType);
        std::shared_ptr<SDL_Texture> GenerateWallTexture(WallType wallType);
        std::shared_ptr<SDL_Texture> GenerateOtherTexture(OtherType otherType);
        std::shared_ptr<SDL_Texture> GenerateTexture(const char* filePath);

        public:
        TextureManager();
        explicit TextureManager(const std::shared_ptr<SDL_Renderer>& renderHandler);
        std::shared_ptr<SDL_Texture> GetTexturePtr(TextureType type, int subType);
        std::shared_ptr<SDL_Texture> GetTexture(ItemType itemType);
        std::shared_ptr<SDL_Texture> GetTexture(PlatformType platformType);
        std::shared_ptr<SDL_Texture> GetTexture(WallType wallType);
        std::shared_ptr<SDL_Texture> GetTexture(OtherType otherType);

        void Render(const std::shared_ptr<SDL_Texture>& texture, const SDL_Rect& shape);
    };

} // namespace GUI

#endif /* C9926753_4601_4BBC_A18B_95D28733B4E7 */
