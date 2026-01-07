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

constexpr int WIDE_BUTTON_WIDTH = TILE_SIZE * 3;
constexpr int BUTTON_HEIGHT = TILE_SIZE;
constexpr int LEFT_ALIGN_POS = RIGHT_MID - static_cast<int>(TILE_SIZE * 1.5);
constexpr int TOP_ALIGN_POS = 10;
constexpr int BUTTON_SPACING = TILE_SIZE / 5;

GUI::Controls::Controls() {
}

GUI::Controls::Controls(const std::shared_ptr<RenderData_t>& renderData) : renderData_(renderData) {
    if (renderData_ == nullptr) {
        std::cout << "Controls: Controls to nullptr\n";
        return;
    }
    int topY = TOP_ALIGN_POS;
    int leftX = LEFT_ALIGN_POS;
    std::string initStr = "0";
    int i = 0;

    // Increment Stage
    tileButtons[i] = TileButton(
        renderData, leftX, topY, [renderData = renderData_]() { renderData->data->UpdateStage(1); }, UP_ARROW);
    // Decrement Stage
    tileButtons[i + 1] = TileButton(
        renderData_, leftX + (TILE_SIZE * 2), topY, [renderData = renderData_]() { renderData->data->UpdateStage(-1); },
        DOWN_ARROW);
    // Stage Text Background
    tileButtonTextBackground[i] = Rectangle(renderData_, leftX + TILE_SIZE, topY, TILE_SIZE, TILE_SIZE);
    // Stage Text
    tileButtonText[i] = Text(renderData_, leftX + static_cast<int>(TILE_SIZE * 1.4), topY, initStr, false);

    ++i;
    topY += BUTTON_HEIGHT + BUTTON_SPACING;

    // Increment Sub-Stage
    tileButtons[i * 2] = TileButton(
        renderData_, leftX, topY, [renderData = renderData_]() { renderData->data->UpdateSubStage(1); }, UP_ARROW);
    // Decrement Sub-Stage
    tileButtons[(i * 2) + 1] = TileButton(
        renderData_, leftX + (TILE_SIZE * 2), topY,
        [renderData = renderData_]() { renderData->data->UpdateSubStage(-1); }, DOWN_ARROW);
    // Sub-Stage Text Background
    tileButtonTextBackground[i] = Rectangle(renderData_, leftX + TILE_SIZE, topY, TILE_SIZE, TILE_SIZE);
    // Sub-Stage Text
    tileButtonText[i] = Text(renderData_, leftX + static_cast<int>(TILE_SIZE * 1.4), topY, initStr, false);

    i = 0;
    topY += BUTTON_HEIGHT + BUTTON_SPACING;
    // Load New Level
    textButtons[0] = TextButton(
        renderData_, leftX, topY, WIDE_BUTTON_WIDTH, BUTTON_HEIGHT,
        [renderData = renderData_]() { renderData->data->SetChangeLevel(true); }, true);
    textButtons[0].text.UpdateText("Load");

    topY += BUTTON_HEIGHT + BUTTON_SPACING;
    // Restart Solver
    textButtons[1] = TextButton(renderData_, leftX, topY, WIDE_BUTTON_WIDTH, BUTTON_HEIGHT, NULL, true);
    textButtons[1].text.UpdateText("Solve");
}

void GUI::Controls::CheckClicked(const Coord_t& coord) {
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
    tileButtonText[0].UpdateText(renderData_->data->GetLevel().stage);
    tileButtonText[1].UpdateText(renderData_->data->GetLevel().subStage);

    // Update and draw
    for (int i = 0; i < 2; ++i) {
        tileButtonTextBackground[i].Draw(BCK_GRND_COL);
        tileButtonText[i].Draw();
    }
}
