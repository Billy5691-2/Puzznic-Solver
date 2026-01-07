#include "include/controls.hpp"
#include <iostream>
#include <string>
#include "constants.hpp"
#include "enums.hpp"
#include "include/board_buttons.hpp"
#include "include/button_types.hpp"
#include "include/gui_data.hpp"
#include "include/rectangle.hpp"
#include "include/text.hpp"

const int WIDE_BUTTON_WIDTH = TILE_SIZE * 3;
const int BUTTON_WIDTH = TILE_SIZE;
const int BUTTON_HEIGHT = TILE_SIZE;
const int LEFT_ALIGN_POS = RIGHT_MID - static_cast<int>(TILE_SIZE * 1.5);
const int TOP_ALIGN_POS = 10;
const int BUTTON_SPACING = TILE_SIZE / 5;

GUI::Controls::Controls() {
    std::cout << "Controls: Default" << std::endl;
}

GUI::Controls::Controls(const std::shared_ptr<RenderData_t>& renderData) : renderData_(renderData) {
    std::cout << "Controls: Main" << std::endl;
    if (renderData_ == nullptr) {
        return;
    }
    int topY = TOP_ALIGN_POS;
    int leftX = LEFT_ALIGN_POS;
    std::string initStr = "0";
    int i = 0;

    // Increment Level
    tileButtons[i] = TileButton(renderData, leftX, topY, [&]() { renderData_->data->UpdateLevel(1); }, UP_ARROW);
    // Decrement Level
    tileButtons[i + 1] = TileButton(
        renderData_, leftX + (TILE_SIZE * 2), topY, [&]() { renderData_->data->UpdateLevel(-1); }, DOWN_ARROW);
    // Level Text Background
    tileButtonTextBackground[i] = Rectangle(renderData_, leftX + TILE_SIZE, topY, TILE_SIZE, TILE_SIZE);
    // Level Text
    tileButtonText[i] = Text(renderData_, leftX + TILE_SIZE, topY, initStr);

    ++i;
    topY += BUTTON_HEIGHT + BUTTON_SPACING;

    // Increment Level
    tileButtons[i * 2] = TileButton(renderData_, leftX, topY, [&]() { renderData_->data->UpdateStage(1); }, UP_ARROW);
    // Decrement Level
    tileButtons[(i * 2) + 1] = TileButton(
        renderData_, leftX + (TILE_SIZE * 2), topY, [&]() { renderData_->data->UpdateStage(-1); }, DOWN_ARROW);
    // Level Text Background
    tileButtonTextBackground[i] = Rectangle(renderData_, leftX + TILE_SIZE, topY, TILE_SIZE, TILE_SIZE);
    // Level Text
    tileButtonText[i] = Text(renderData_, leftX + TILE_SIZE, topY, initStr);

    i = 0;
    topY += BUTTON_HEIGHT + BUTTON_SPACING;
    // Load New Level
    textButtons[0] = TextButton(renderData_, leftX, topY, WIDE_BUTTON_WIDTH, BUTTON_HEIGHT,
                                [&]() { renderData_->data->SetChangeLevel(true); });

    topY += BUTTON_HEIGHT + BUTTON_SPACING;
    // Restart Solver
    textButtons[1] = TextButton(renderData_, leftX, topY, WIDE_BUTTON_WIDTH, BUTTON_HEIGHT, NULL);
    std::cout << "Controls: Complete" << std::endl;
}

void GUI::Controls::CheckClicked(const Coord& coord) {
    for (int i = 0; i < NUMBER_OF_TEXT_BUTTONS; ++i) {
        if (textButtons[i].button.ClickedButton(coord)) {
            return;
        }
    }

    for (int i = 0; i < NUMBER_OF_TILE_BUTTONS; ++i) {
        if (tileButtons[i].button.ClickedButton(coord)) {
            return;
        }
    }

    BoardButtons::CheckClicked(renderData_, coord);
}

void GUI::Controls::Draw() {
    // Draw Text buttons
    for (int i = 0; i < NUMBER_OF_TEXT_BUTTONS; ++i) {
        textButtons[i].Draw();
    }

    // Draw tile buttons
    for (int i = 0; i < NUMBER_OF_TILE_BUTTONS; ++i) {
        tileButtons[i].Draw();
    }

    // Update tile button text
    tileButtonText[0].UpdateText(renderData_->data->GetLevel());
    tileButtonText[1].UpdateText(renderData_->data->GetStage());

    // Update and draw
    for (int i = 0; i < 2; ++i) {
        tileButtonTextBackground[i].Draw(BCK_GRND_COL);
        tileButtonText[i].Draw();
    }
}

// void GUI::Controls::Free() {
//     for (int i = 0; i < NUMBER_OF_TEXT_BUTTONS; ++i) {
//         textButtons[i].Free();
//     }
//     for (int i = 0; i < 2; ++i) {
//         tileButtonText[i].Free();
//     }
// }
