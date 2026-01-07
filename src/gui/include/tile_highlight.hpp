#ifndef FB84CC8F_8CAF_4C28_B19C_100B4D64FB53
#define FB84CC8F_8CAF_4C28_B19C_100B4D64FB53

#include <memory>
#include "SDL2/SDL_pixels.h"
#include "SDL_rect.h"
#include "gui_data.hpp"
#include "rectangle.hpp"

static constexpr SDL_Colour HighlightColour = {255, 245, 40, 0};

namespace GUI {
    class TileHighlight {
        std::shared_ptr<RenderData_t> renderData_;
        SDL_Rect rect_ = {0, 0, 0, 0};

        public:
        TileHighlight();
        explicit TileHighlight(const std::shared_ptr<RenderData_t>& renderData);
        void Draw();
    };
} // namespace GUI

#endif /* FB84CC8F_8CAF_4C28_B19C_100B4D64FB53 */
