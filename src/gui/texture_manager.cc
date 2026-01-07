#include "include/texture_manager.hpp"

#include <SDL2/SDL_render.h>
#include <iostream>
#include <memory>

#include "enums.hpp"
#include "file_paths.hpp"

GUI::TextureManager::TextureManager() {
}

GUI::TextureManager::TextureManager(const std::shared_ptr<SDL_Renderer>& renderHandler, const std::string& basePath)
    : renderHandler_(renderHandler) {
    if (renderHandler_ == nullptr) {
        std::cout << "TextureManager: Got nullptr\n";
        return;
    }
    for (int i = 0; i < NUMBER_OF_ITEMS; ++i) {
        itemTextures_[i] = GenerateItemTexture(static_cast<ItemType>(i), basePath);
    }
    for (int i = 0; i < NUMBER_OF_PLATFORM_TYPES; ++i) {
        platformTextures_[i] = GeneratePlatformTexture(static_cast<PlatformType>(i), basePath);
    }
    for (int i = 0; i < NUMBER_OF_WALL_TYPES; ++i) {
        wallTextures_[i] = GenerateWallTexture(static_cast<WallType>(i), basePath);
    }
    for (int i = 0; i < NUMBER_OF_MISC_TYPES; ++i) {
        miscTextures_[i] = GenerateMiscTexture(static_cast<MiscType>(i), basePath);
    }
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
std::shared_ptr<SDL_Texture> GUI::TextureManager::GetTexture(MiscType type) {
    return miscTextures_[type];
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
        case TEX_MISC: {
            return GetTexture(static_cast<MiscType>(subType));
            break;
        }
        default: {
            std::cout << "GetTexturePtr: Invalid TextureType\n";
            return nullptr;
        }
    }
}

std::shared_ptr<SDL_Texture> GUI::TextureManager::GeneratePlatformTexture(PlatformType platformType,
                                                                          const std::string& basePath) {
    std::string filePathStr = basePath;
    switch (platformType) {
        case UP: {
            filePathStr += UP_PLATFORM_PATH;
            break;
        }
        case DOWN: {
            filePathStr += DOWN_PLATFORM_PATH;
            break;
        }
        case LEFT: {
            filePathStr += LEFT_PLATFORM_PATH;
            break;
        }
        case RIGHT: {
            filePathStr += RIGHT_PLATFORM_PATH;
            break;
        }
        default: {
            std::cout << "Error in Texture Manager - Platform_t\n";
        }
    }
    return GenerateTexture(filePathStr.c_str());
}

std::shared_ptr<SDL_Texture> GUI::TextureManager::GenerateWallTexture(WallType wallType, const std::string& basePath) {
    std::string filePathStr = basePath;
    switch (wallType) {
        case EXTERIOR: {
            filePathStr += EXTERIOR_WALL_PATH;
            break;
        }
        case INTERIOR: {
            filePathStr += INTERIOR_WALL_PATH;
            break;
        }
        case FLOOR: {
            filePathStr += FLOOR_WALL_PATH;
            break;
        }
        case LEDGE: {
            filePathStr += LEDGE_WALL_PATH;
            break;
        }
        default: {
            std::cout << "Error in Texture Manager - Wall\n";
        }
    }
    return GenerateTexture(filePathStr.c_str());
}

std::shared_ptr<SDL_Texture> GUI::TextureManager::GenerateMiscTexture(MiscType MiscType, const std::string& basePath) {
    std::string filePathStr = basePath;
    switch (MiscType) {
        case UP_ARROW: {
            filePathStr += UP_ARROW_PATH;
            break;
        }
        case DOWN_ARROW: {
            filePathStr += DOWN_ARROW_PATH;
            break;
        }
        case MOVE_MARKER: {
            filePathStr += MOVE_MARKER_PATH;
            break;
        }
        default: {
            std::cout << "Error in Texture Manager - Misc\n";
        }
    }
    return GenerateTexture(filePathStr.c_str());
}

std::shared_ptr<SDL_Texture> GUI::TextureManager::GenerateItemTexture(ItemType itemType, const std::string& basePath) {
    std::string filePathStr = basePath;
    switch (itemType) {
        case RED: {
            filePathStr += RED_ITEM_PATH;
            break;
        }
        case BLUE: {
            filePathStr += BLUE_ITEM_PATH;
            break;
        }
        case GREEN: {
            filePathStr += GREEN_ITEM_PATH;
            break;
        }
        case PINK: {
            filePathStr += PINK_ITEM_PATH;
            break;
        }
        case PURPLE: {
            filePathStr += PURPLE_ITEM_PATH;
            break;
        }
        case CYAN: {
            filePathStr += CYAN_ITEM_PATH;
            break;
        }
        case BROWN: {
            filePathStr += BROWN_ITEM_PATH;
            break;
        }
        case ORANGE: {
            filePathStr += ORANGE_ITEM_PATH;
            break;
        }
        case YELLOW: {
            filePathStr += YELLOW_ITEM_PATH;
            break;
        }
        default: {
            std::cout << "Error in Texture Manager - Platform_t\n";
        }
    }
    return GenerateTexture(filePathStr.c_str());
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
