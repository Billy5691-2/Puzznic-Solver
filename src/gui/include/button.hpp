#ifndef FE34B26E_898B_4278_872A_1EB88857CC45
#define FE34B26E_898B_4278_872A_1EB88857CC45

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <functional>
#include <memory>
#include "../../common/structs.hpp"
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_rect.h"

namespace GUI {
    class Button {
        SDL_Rect rect_ = SDL_Rect();
        std::function<void()> effect_;
        bool clicked_ = false;

        void ResetClicked();

        public:
        Button();
        Button(int width, int height, int x, int y, std::function<void()> effect);

        bool ClickedButton(const Coord_t&);

        bool IsClicked();
    };
} // namespace GUI

#endif /* FE34B26E_898B_4278_872A_1EB88857CC45 */
