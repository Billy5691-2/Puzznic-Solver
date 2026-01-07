#ifndef F099EE7B_3996_4D18_BBFF_DD4246993DD2
#define F099EE7B_3996_4D18_BBFF_DD4246993DD2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <array>
#include <map>
#include <memory>

#include "../../common/constants.hpp"
#include "../../common/enums.hpp"
#include "../../common/structs.hpp"
#include "gui_data.hpp"
#include "text.hpp"
#include "tile_manager.hpp"

namespace GUI {
    class ItemCounter {
        std::shared_ptr<RenderData_t> renderData_ = nullptr;
        std::array<TileManager, NUMBER_OF_ITEMS> itemCountTilesArr_;
        std::array<Text, NUMBER_OF_ITEMS> itemCountTextArr_;

        public:
        ItemCounter();
        explicit ItemCounter(const std::shared_ptr<RenderData_t>& renderData);

        void Draw();
    };
} // namespace GUI

#endif /* F099EE7B_3996_4D18_BBFF_DD4246993DD2 */
