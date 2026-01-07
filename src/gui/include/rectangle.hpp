#ifndef CD31CF89_3595_4D53_B8C6_4A43920D0636
#define CD31CF89_3595_4D53_B8C6_4A43920D0636

#include <memory>
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "gui_data.hpp"

constexpr SDL_Colour BCK_GRND_COL = {80, 80, 80, 0}; ///< Background colour
constexpr SDL_Colour CLKD_COL = {100, 100, 100, 0};  ///< Clicked colour
constexpr SDL_Colour BRDER_COL = {255, 200, 50, 0};  ///< Border colour

namespace GUI {
    class Rectangle {
        std::shared_ptr<RenderData_t> renderData_ = nullptr;
        SDL_Rect rect_;

        public:
        Rectangle();
        Rectangle(const std::shared_ptr<RenderData_t>& renderData, int x, int y, int w, int h);

        void SetPosition(const Coord_t& coord);
        void Draw(const SDL_Colour& textColour);
    };
}; // namespace GUI

#endif /* CD31CF89_3595_4D53_B8C6_4A43920D0636 */
