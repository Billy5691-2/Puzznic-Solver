#ifndef CA7C55B0_F404_42C7_AAE0_21528183786D
#define CA7C55B0_F404_42C7_AAE0_21528183786D

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#include <memory>

#include "../../common/enums.hpp"
#include "../../common/structs.hpp"
#include "gui_data.hpp"
#include "texture_manager.hpp"

namespace GUI {
    class TileManager {
        std::shared_ptr<RenderData_t> renderData_ = nullptr;
        SDL_Rect tileShape_ = {};
        std::shared_ptr<SDL_Texture> tileTexture_ = nullptr;
        TileManager(const std::shared_ptr<RenderData_t>& renderHandler, const std::shared_ptr<SDL_Texture>& texture);

        public:
        TileManager();
        TileManager(const std::shared_ptr<RenderData_t>& renderHandler, PlatformType platformType);
        TileManager(const std::shared_ptr<RenderData_t>& renderHandler, ItemType itemType);
        TileManager(const std::shared_ptr<RenderData_t>& renderHandler, WallType wallType);
        TileManager(const std::shared_ptr<RenderData_t>& renderHandler, MiscType MiscType);

        void SetPosition(int x, int y);
        void SetPosition(const Coord_t& pixel);
        void Draw();
    };
} // namespace GUI

#endif /* CA7C55B0_F404_42C7_AAE0_21528183786D */
