#include "include/board.hpp"
#include <memory>
#include "constants.hpp"
#include "enums.hpp"
#include "include/board_background.hpp"
#include "include/gui_data.hpp"
#include "include/texture_manager.hpp"
#include "include/tile_highlight.hpp"
#include "include/tile_manager.hpp"
#include "structs.hpp"

GUI::Board::Board() {
    std::cout << "Board: Default" << std::endl;
}

GUI::Board::Board(const std::shared_ptr<RenderData_t>& renderData)
    : renderData_(renderData), background_(renderData), tileHighlight_(renderData) {
    std::cout << "Board: Main" << std::endl;
    if (renderData_ == nullptr) {
        return;
    }
    const std::array<std::array<WallType, BOARD_SIZE>, BOARD_SIZE>& wallData = renderData_->data->GetWalls();
    int i = 0;
    for (int x = 0; x < BOARD_SIZE; ++x) {
        for (int y = 0; y < BOARD_SIZE; ++y) {
            if (wallData[x][y] != WALL_NONE) {
                wallTiles_[i] = TileManager(renderData_, wallData[x][y]);
                wallTiles_[i].SetPosition(x, y);
                ++i;
            }
        }
    }

    const std::map<int, Item>& items = renderData_->data->GetItems();
    for (const auto& [key, item] : items) {
        itemTiles_[key].texture = TileManager(renderData_, item.type);
        itemTiles_[key].texture.SetPosition(item.position);
    }

    const std::map<int, Platform>& platforms = renderData_->data->GetPlatforms();
    for (const auto& [key, platform] : platforms) {
        if (platform.direction == UP || platform.direction == DOWN) {
            platformTiles_[key].textures[UP] = TileManager(renderData_, UP);
            platformTiles_[key].textures[DOWN] = TileManager(renderData_, DOWN);
            platformTiles_[key].currentDirection = platform.direction;
            platformTiles_[key].position = platform.pos;

        } else if (platform.direction == LEFT || platform.direction == RIGHT) {
            platformTiles_[key].textures[LEFT] = TileManager(renderData_, LEFT);
            platformTiles_[key].textures[RIGHT] = TileManager(renderData_, RIGHT);
            platformTiles_[key].currentDirection = platform.direction;
            platformTiles_[key].position = platform.pos;
        }
    }
    std::cout << "Board: Complete" << std::endl;
}

void GUI::Board::UpdatePlatforms() {
    const std::map<int, Platform>& platforms = renderData_->data->GetPlatforms();
    for (const auto& [key, platform] : platforms) {
        platformTiles_[key].currentDirection = platform.direction;
        platformTiles_[key].position = platform.pos;
    }
}

void GUI::Board::UpdateItems() {
    const std::map<int, Item>& items = renderData_->data->GetItems();
    for (const auto& [key, item] : items) {
        itemTiles_[key].texture.SetPosition(item.position);
        itemTiles_[key].destroyed = item.deleted;
    }
}

void GUI::Board::DrawWalls() {
    for (const auto& [key, wall] : wallTiles_) {
        wallTiles_[key].Draw();
    }
}

void GUI::Board::DrawPlatforms() {
    for (const auto& [key, platform] : platformTiles_) {
        platformTiles_[key].textures[platform.currentDirection].SetPosition(platform.position);
        platformTiles_[key].textures[platform.currentDirection].Draw();
    }
}

void GUI::Board::DrawItems() {
    for (const auto& [key, item] : itemTiles_) {
        if (!item.destroyed) {
            itemTiles_[key].texture.Draw();
        }
    }
}

void GUI::Board::DrawMoves() {
    const std::vector<Coord>& moves = renderData_->data->GetMoves();
    for (const auto& move : moves) {
        moveTexture_.SetPosition(move);
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