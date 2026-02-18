#include "include/board.hpp"
#include <bits/c++config.h>
#include <memory>
#include "constants.hpp"
#include "enums.hpp"
#include "include/board_background.hpp"
#include "include/board_buttons.hpp"
#include "include/gui_data.hpp"
#include "include/texture_manager.hpp"
#include "include/tile_highlight.hpp"
#include "include/tile_manager.hpp"
#include "structs.hpp"

GUI::Board::Board() {
}

GUI::Board::Board(const std::shared_ptr<RenderData_t>& renderData)
    : renderData_(renderData), background_(renderData), tileHighlight_(renderData) {
    if (renderData_ == nullptr) {
        std::cout << "Board: Constructor got nullptr\n";
        return;
    }
    const std::array<std::array<WallType, BOARD_SIZE>, BOARD_SIZE>& wallData = renderData_->data->GetWalls();
    int i = 0;
    for (int x = 0; x < BOARD_SIZE; ++x) {
        for (int y = 0; y < BOARD_SIZE; ++y) {
            if (wallData[x][y] != WALL_NONE) {
                wallTiles_[i] = TileManager(renderData_, wallData[x][y]);
                wallTiles_[i].SetPosition(BoardButtons::ConvertToPixel({x, y}));
                ++i;
            }
        }
    }

    const std::vector<Item_t>& items = renderData_->data->GetItems();
    itemTiles_.resize(items.size());
    for (std::size_t i = 0; i < items.size(); ++i) {
        itemTiles_[i].texture = TileManager(renderData_, items[i].type);
        itemTiles_[i].texture.SetPosition(BoardButtons::ConvertToPixel(items[i].position));
    }

    const std::vector<Platform_t>& platforms = renderData_->data->GetPlatforms();
    platformTiles_.resize(platforms.size());
    for (std::size_t i = 0; i < platforms.size(); ++i) {
        if (platforms[i].direction == UP || platforms[i].direction == DOWN) {
            platformTiles_[i].textures[UP] = TileManager(renderData_, UP);
            platformTiles_[i].textures[DOWN] = TileManager(renderData_, DOWN);
        } else if (platforms[i].direction == LEFT || platforms[i].direction == RIGHT) {
            platformTiles_[i].textures[LEFT] = TileManager(renderData_, LEFT);
            platformTiles_[i].textures[RIGHT] = TileManager(renderData_, RIGHT);
        }
        platformTiles_[i].currentDirection = platforms[i].direction;
        platformTiles_[i].position = BoardButtons::ConvertToPixel(platforms[i].pos);
    }
}

/* ###################### Update ######################## */
void GUI::Board::UpdatePlatforms() {
    const std::vector<Platform_t>& platforms = renderData_->data->GetPlatforms();
    for (std::size_t i = 0; i < platforms.size(); ++i) {
        platformTiles_[i].currentDirection = platforms[i].direction;
        platformTiles_[i].position = BoardButtons::ConvertToPixel(platforms[i].pos);
    }
}

void GUI::Board::UpdateItems() {
    const std::vector<Item_t>& items = renderData_->data->GetItems();
    for (std::size_t i = 0; i < items.size(); ++i) {
        itemTiles_[i].texture.SetPosition(BoardButtons::ConvertToPixel(items[i].position));
        itemTiles_[i].destroyed = items[i].deleted;
    }
}


/* ###################### Draw ######################## */
void GUI::Board::DrawWalls() {
    for (const auto& [key, wall] : wallTiles_) {
        wallTiles_[key].Draw();
    }
}

void GUI::Board::DrawPlatforms() {
    for (auto& platform : platformTiles_) {
        platform.textures[platform.currentDirection].SetPosition(platform.position);
        platform.textures[platform.currentDirection].Draw();
    }
}

void GUI::Board::DrawItems() {
    for (auto& item : itemTiles_) {
        if (!item.destroyed) {
            item.texture.Draw();
        }
    }
}

void GUI::Board::DrawMoves() {
    const std::vector<Coord_t>& moves = renderData_->data->GetMoves();
    for (const auto& move : moves) {
        moveTexture_.SetPosition(BoardButtons::ConvertToPixel(move));
        moveTexture_.Draw();
    }
}

void GUI::Board::Draw() {
    UpdatePlatforms();
    UpdateItems();
    background_.DrawBackground();
    DrawWalls();
    DrawPlatforms();
    DrawItems();
    DrawMoves();
    tileHighlight_.Draw();
}