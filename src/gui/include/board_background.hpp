#ifndef C96E4EBB_025D_43FF_91B4_E54AE1065E68
#define C96E4EBB_025D_43FF_91B4_E54AE1065E68
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <memory>
#include "gui_data.hpp"

namespace GUI {
    class BoardBackground {
        std::shared_ptr<RenderData_t> renderData_ = nullptr;

        public:
        BoardBackground();
        explicit BoardBackground(const std::shared_ptr<RenderData_t>& renderData);
        void DrawBackground();
    };
} // namespace GUI

#endif /* C96E4EBB_025D_43FF_91B4_E54AE1065E68 */
