#ifndef A74D9821_FEA0_43F4_97DF_2F438CCCB621
#define A74D9821_FEA0_43F4_97DF_2F438CCCB621

#include <array>
#include <memory>

#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"

#include "board_buttons.hpp"
#include "button.hpp"
#include "button_types.hpp"
#include "gui_data.hpp"
#include "rectangle.hpp"
#include "structs.hpp"
#include "text.hpp"
#include "tile_manager.hpp"

const int NUMBER_OF_TEXT_BUTTONS = 2;
const int NUMBER_OF_TILE_BUTTONS = 4;

namespace GUI {
    class Controls {
        std::shared_ptr<RenderData_t> renderData_ = nullptr;
        std::array<Text, 2> tileButtonText;
        std::array<Rectangle, 2> tileButtonTextBackground;
        std::array<TextButton, NUMBER_OF_TEXT_BUTTONS> textButtons;
        std::array<TileButton, NUMBER_OF_TILE_BUTTONS> tileButtons;

        public:
        Controls();
        explicit Controls(const std::shared_ptr<RenderData_t>& renderData);
        void CheckClicked(const Coord_t& coord);
        void Draw();
    };
}; // namespace GUI

#endif /* A74D9821_FEA0_43F4_97DF_2F438CCCB621 */
