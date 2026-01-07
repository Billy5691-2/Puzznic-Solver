#ifndef FB84CC8F_8CAF_4C28_B19C_100B4D64FB53
#define FB84CC8F_8CAF_4C28_B19C_100B4D64FB53

#include <memory>
#include "SDL2/SDL_pixels.h"
#include "gui_data.hpp"
#include "rectangle.hpp"

static const SDL_Colour HighlightColour = {0, 100, 100, 0};

namespace GUI {
    class TileHighlight {
        std::shared_ptr<RenderData_t> renderData_;
        Rectangle rect_;
        bool draw_ = false;

        public:
        TileHighlight();
        explicit TileHighlight(const std::shared_ptr<RenderData_t>& renderData);
        void Draw();
    };
} // namespace GUI

#endif /* FB84CC8F_8CAF_4C28_B19C_100B4D64FB53 */
