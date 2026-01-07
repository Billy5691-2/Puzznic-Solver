#ifndef DAEA4AB5_65FD_4FA0_96D7_78F006A5F6E1
#define DAEA4AB5_65FD_4FA0_96D7_78F006A5F6E1

#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"
#include "SDL2/SDL_ttf.h"
#include "gui_data.hpp"

constexpr SDL_Colour TXT_COL = {0, 255, 255, 0}; ///< Text Colour

namespace GUI {
    struct SurfaceDeleter {
        void operator()(SDL_Surface* surface) const {
            if (surface) {
                SDL_FreeSurface(surface);
            }
        }
    };

    using SurfacePtr = std::unique_ptr<SDL_Surface, SurfaceDeleter>;

    struct TextureDeleter {
        void operator()(SDL_Texture* texture) const {
            if (texture) {
                SDL_DestroyTexture(texture);
            }
        }
    };

    using TexturePtr = std::unique_ptr<SDL_Texture, TextureDeleter>;

    class Text {
        std::string text_;

        SDL_Rect rect_ = SDL_Rect();
        SurfacePtr surface_ = nullptr;
        TexturePtr texture_ = nullptr;
        std::shared_ptr<RenderData_t> renderData_ = nullptr;
        int x_ = 0;
        int y_ = 0;
        bool centered_ = false;

        public:
        Text();
        Text(const std::shared_ptr<RenderData_t>& renderData, int x, int y, const std::string& message, bool centered);
        void UpdateTexture();
        void UpdateText(const std::string&);
        void UpdateText(int);
        void Draw();
    };
}; // namespace GUI

#endif /* DAEA4AB5_65FD_4FA0_96D7_78F006A5F6E1 */
