#ifndef CD31CF89_3595_4D53_B8C6_4A43920D0636
#define CD31CF89_3595_4D53_B8C6_4A43920D0636

#include <memory>
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "gui_data.hpp"

const SDL_Colour BCK_GRND_COL = {200, 200, 200, 0}; ///< Background colour
const SDL_Colour CLKD_COL = {200, 200, 200, 0};     ///< Clicked colour
const SDL_Colour BRDER_COL = {200, 200, 200, 0};    ///< Border colour

namespace GUI {
    class Rectangle {
        SDL_Rect rect_;
        std::shared_ptr<RenderData_t> renderData_ = NULL;

       public:
        Rectangle();
        Rectangle(const std::shared_ptr<RenderData_t>& renderData, int x, int y, int w, int h);

        void SetPosition(const Coord& coord);
        void Draw(const SDL_Colour& textColour);
    };
}; // namespace GUI

#endif /* CD31CF89_3595_4D53_B8C6_4A43920D0636 */
