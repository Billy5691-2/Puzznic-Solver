#ifndef F62DBB3F_3EA4_4D51_A4FD_6D52C3BA52D2
#define F62DBB3F_3EA4_4D51_A4FD_6D52C3BA52D2

#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include "SDL2/SDL_render.h"

#include "button.hpp"
#include "constants.hpp"
#include "enums.hpp"
#include "gui_data.hpp"
#include "rectangle.hpp"
#include "text.hpp"
#include "tile_manager.hpp"

namespace GUI {
    class TextButton {
        public:
        Button button = Button(0, 0, 0, 0, NULL);
        Rectangle rectangle = Rectangle(nullptr, 0, 0, 0, 0);
        Text text = Text();

        TextButton(const std::shared_ptr<RenderData_t>& renderData, int x, int y, int w, int h,
                   const std::function<void()>& function, bool centered) {
            button = Button(w, h, x, y, function);
            rectangle = Rectangle(renderData, x, y, w, h);
            std::string initialValue = "0";
            text = Text(renderData, x + (w / 2), y + (h / 2), initialValue, centered);
        }
        TextButton() {
        }

        void Draw() {
            if (button.IsClicked()) {
                rectangle.Draw(CLKD_COL);
            } else {
                rectangle.Draw(BCK_GRND_COL);
            }
            text.Draw();
        }
    };

    class TileButton {
        public:
        Button button = Button(0, 0, 0, 0, NULL);
        TileManager tile;

        TileButton(const std::shared_ptr<RenderData_t>& renderData, int x, int y, const std::function<void()>& function,
                   MiscType tileType) {
            button = Button(TILE_SIZE, TILE_SIZE, x, y, function);
            tile = TileManager(renderData, tileType);
            tile.SetPosition(x, y);
        }
        TileButton() {
        }

        void Draw() {
            tile.Draw();
        }
    };

}; // namespace GUI

#endif /* F62DBB3F_3EA4_4D51_A4FD_6D52C3BA52D2 */
