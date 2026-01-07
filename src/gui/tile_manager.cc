#include "include/tile_manager.hpp"
#include <iostream>
#include <memory>
#include "../common/enums.hpp"
#include "../common/structs.hpp"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "constants.hpp"
#include "include/gui_data.hpp"
#include "include/texture_manager.hpp"

GUI::TileManager::TileManager() {
}
GUI::TileManager::TileManager(const std::shared_ptr<RenderData_t>& renderData,
                              const std::shared_ptr<SDL_Texture>& texture)
    : renderData_(renderData), tileTexture_(texture) {
    tileShape_.w = TILE_SIZE;
    tileShape_.h = TILE_SIZE;
}
GUI::TileManager::TileManager(const std::shared_ptr<RenderData_t>& renderHandler, PlatformType platformType)
    : TileManager(renderHandler, renderHandler->textures.GetTexture(platformType)) {
}
GUI::TileManager::TileManager(const std::shared_ptr<RenderData_t>& renderHandler, ItemType itemType)
    : TileManager(renderHandler, renderHandler->textures.GetTexture(itemType)) {
}
GUI::TileManager::TileManager(const std::shared_ptr<RenderData_t>& renderHandler, WallType wallType)
    : TileManager(renderHandler, renderHandler->textures.GetTexture(wallType)) {
}
GUI::TileManager::TileManager(const std::shared_ptr<RenderData_t>& renderHandler, MiscType MiscType)
    : TileManager(renderHandler, renderHandler->textures.GetTexture(MiscType)) {
}

// Set the position of a tile in the board
void GUI::TileManager::SetPosition(int x, int y) {
    tileShape_.x = x;
    tileShape_.y = y;
}

void GUI::TileManager::SetPosition(const Coord_t& pixel) {
    SetPosition(pixel.x, pixel.y);
}

// Renders a tile's texture on the board
void GUI::TileManager::Draw() {
    renderData_->textures.Render(tileTexture_, tileShape_);
}
