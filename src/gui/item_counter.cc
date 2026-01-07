#include "include/item_counter.hpp"
#include "include/gui_data.hpp"
#include "include/text.hpp"
#include "include/texture_manager.hpp"
#include "include/tile_manager.hpp"

#include "../common/constants.hpp"
#include "../common/enums.hpp"
#include "../common/structs.hpp"

#include <SDL2/SDL.h>
#include <array>
#include <iostream>
#include <map>

GUI::ItemCounter::ItemCounter() {
    std::cout << "ItemCounter: Default" << std::endl;
}

GUI::ItemCounter::ItemCounter(const std::shared_ptr<RenderData_t>& renderData) : renderData_(renderData) {
    std::cout << "ItemCounter: Main" << std::endl;
    if (renderData_ == nullptr) {
        return;
    }
    int x = 0;
    int y = 0;
    std::string defaultTxt = "x0";
    for (int i = 0; i < NUMBER_OF_ITEMS; ++i) {
        x = WINDOW_LEFT / 4;
        y = TILE_SIZE + (i * (TILE_SIZE + 10));
        TileManager temp = TileManager(renderData_, static_cast<ItemType>(i));
        temp.SetPosition(x, y);
        itemCountTilesArr_[i] = TileManager(renderData_, static_cast<ItemType>(i));

        itemCountTextArr_[i] = Text(renderData_, static_cast<int>(x + (TILE_SIZE * 1.5)), y, defaultTxt);
    }
    std::cout << "ItemCounter: Complete" << std::endl;
}

void GUI::ItemCounter::Draw() {
    const std::array<int, NUMBER_OF_ITEMS>& itemCount = renderData_->data->GetItemCount();
    for (int i = 0; i < NUMBER_OF_ITEMS; ++i) {
        std::string intermediateString = "x" + std::to_string(itemCount[i]);
        itemCountTextArr_[i].UpdateText(intermediateString);
        itemCountTextArr_[i].Draw();

        itemCountTilesArr_[i].Draw();
    }
}

// void GUI::ItemCounter::Free() {
//     for (int i = 0; i < NUMBER_OF_ITEMS; ++i) {
//         itemCountTextArr_[i].Free();
//     }
// }
