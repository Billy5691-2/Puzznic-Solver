#include "include/texture_manager.hpp"
#include "../common/enums.hpp"
#include "SDL2/SDL_render.h"

#include <iostream>
#include <memory>

GUI::TextureManager::TextureManager() {
    std::cout << "TextureManager: Default" << std::endl;
}

GUI::TextureManager::TextureManager(const std::shared_ptr<SDL_Renderer>& renderHandler)
    : renderHandler_(renderHandler) {
    std::cout << "TextureManager: Main" << std::endl;
    if (renderHandler_ == nullptr) {
        return;
    }
    for (int i = 0; i < NUMBER_OF_ITEMS; ++i) {
        itemTextures_[i] = GenerateItemTexture(static_cast<ItemType>(i));
    }
    for (int i = 0; i < NUMBER_OF_PLATFORM_TYPES; ++i) {
        platformTextures_[i] = GeneratePlatformTexture(static_cast<PlatformType>(i));
    }
    for (int i = 0; i < NUMBER_OF_WALL_TYPES; ++i) {
        wallTextures_[i] = GenerateWallTexture(static_cast<WallType>(i));
    }
    for (int i = 0; i < NUMBER_OF_ITEMS; ++i) {
        otherTextures_[i] = GenerateOtherTexture(static_cast<OtherType>(i));
    }
    std::cout << "TextureManager: Complete" << std::endl;
}

std::shared_ptr<SDL_Texture> GUI::TextureManager::GetTexture(ItemType type) {
    return itemTextures_[type];
}
std::shared_ptr<SDL_Texture> GUI::TextureManager::GetTexture(PlatformType type) {
    return platformTextures_[type];
}
std::shared_ptr<SDL_Texture> GUI::TextureManager::GetTexture(WallType type) {
    return wallTextures_[type];
}
std::shared_ptr<SDL_Texture> GUI::TextureManager::GetTexture(OtherType type) {
    return otherTextures_[type];
}

std::shared_ptr<SDL_Texture> GUI::TextureManager::GetTexturePtr(TextureType type, int subType) {
    switch (type) {
        case TEX_ITEM: {
            return GetTexture(static_cast<ItemType>(subType));
            break;
        }
        case TEX_PLATFORM: {
            return GetTexture(static_cast<PlatformType>(subType));
            break;
        }
        case TEX_WALL: {
            return GetTexture(static_cast<WallType>(subType));
            break;
        }
        case TEX_OTHER: {
            return GetTexture(static_cast<OtherType>(subType));
            break;
        }
        default: {
            std::cout << "GetTexturePtr: Invalid TextureType\n";
            return nullptr;
        }
    }
}

std::shared_ptr<SDL_Texture> GUI::TextureManager::GeneratePlatformTexture(PlatformType platformType) {
    const char* filePath = NULL;
    SDL_Texture* texture = NULL;
    switch (platformType) {
        case UP: {
            filePath = UP_PLATFORM_PATH;
            break;
        }
        case DOWN: {
            filePath = DOWN_PLATFORM_PATH;
            break;
        }
        case LEFT: {
            filePath = LEFT_PLATFORM_PATH;
            break;
        }
        case RIGHT: {
            filePath = RIGHT_PLATFORM_PATH;
            break;
        }
        default: {
            std::cout << "Error in Texture Manager - Platform\n";
        }
    }
    return GenerateTexture(filePath);
}

std::shared_ptr<SDL_Texture> GUI::TextureManager::GenerateWallTexture(WallType wallType) {
    const char* filePath = NULL;
    SDL_Texture* texture = NULL;
    switch (wallType) {
        case EXTERIOR: {
            filePath = EXTERIOR_WALL_PATH;
            break;
        }
        case INTERIOR: {
            filePath = INTERIOR_WALL_PATH;
            break;
        }
        case FLOOR: {
            filePath = FLOOR_WALL_PATH;
            break;
        }
        case LEDGE: {
            filePath = LEDGE_WALL_PATH;
            break;
        }
        default: {
            std::cout << "Error in Texture Manager - Platform\n";
        }
    }
    return GenerateTexture(filePath);
}

std::shared_ptr<SDL_Texture> GUI::TextureManager::GenerateOtherTexture(OtherType otherType) {
    const char* filePath = NULL;
    SDL_Texture* texture = NULL;
    switch (otherType) {
        case UP_ARROW: {
            filePath = UP_ARROW_PATH;
            break;
        }
        case DOWN_ARROW: {
            filePath = DOWN_ARROW_PATH;
            break;
        }
        case MOVE_MARKER: {
            filePath = MOVE_MARKER_PATH;
            break;
        }
        default: {
            std::cout << "Error in Texture Manager - Platform\n";
        }
    }
    return GenerateTexture(filePath);
}

std::shared_ptr<SDL_Texture> GUI::TextureManager::GenerateItemTexture(ItemType itemType) {
    const char* filePath = NULL;
    SDL_Texture* texture = NULL;
    switch (itemType) {
        case RED: {
            filePath = RED_ITEM_PATH;
            break;
        }
        case BLUE: {
            filePath = BLUE_ITEM_PATH;
            break;
        }
        case GREEN: {
            filePath = GREEN_ITEM_PATH;
            break;
        }
        case PINK: {
            filePath = PINK_ITEM_PATH;
            break;
        }
        case PURPLE: {
            filePath = PURPLE_ITEM_PATH;
            break;
        }
        case CYAN: {
            filePath = CYAN_ITEM_PATH;
            break;
        }
        case BROWN: {
            filePath = BROWN_ITEM_PATH;
            break;
        }
        case ORANGE: {
            filePath = ORANGE_ITEM_PATH;
            break;
        }
        case YELLOW: {
            filePath = YELLOW_ITEM_PATH;
            break;
        }
        default: {
            std::cout << "Error in Texture Manager - Platform\n";
        }
    }
    return GenerateTexture(filePath);
}

std::shared_ptr<SDL_Texture> GUI::TextureManager::GenerateTexture(const char* filePath) {
    std::shared_ptr<SDL_Texture> texture =
        std::shared_ptr<SDL_Texture>(IMG_LoadTexture(renderHandler_.get(), filePath), SDL_DestroyTexture);
    if (texture == nullptr) {
        SDL_Log(
            "Failed to load img from %s \n "
            " {ERROR: %s} \n",
            filePath, SDL_GetError());
        return nullptr;
    }
    return texture;
}

void GUI::TextureManager::Render(const std::shared_ptr<SDL_Texture>& texture, const SDL_Rect& shape) {
    SDL_RenderCopy(renderHandler_.get(), texture.get(), NULL, &shape);
}
