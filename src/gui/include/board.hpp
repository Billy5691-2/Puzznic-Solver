#ifndef BB906A41_1129_4933_BDEE_05B69E639647
#define BB906A41_1129_4933_BDEE_05B69E639647

#include <array>
#include <map>
#include <memory>
#include "SDL2/SDL_render.h"
#include "board_background.hpp"
#include "enums.hpp"
#include "gui_data.hpp"
#include "structs.hpp"
#include "texture_manager.hpp"
#include "tile_highlight.hpp"
#include "tile_manager.hpp"

namespace GUI {
    struct PlatformTile_t {
        std::map<PlatformType, TileManager> textures;
        PlatformType currentDirection;
        Coord_t position;
    };
    struct ItemTile_t {
        TileManager texture;
        bool destroyed = false;
    };
    class Board {
        std::map<int, TileManager> wallTiles_;
        std::vector<PlatformTile_t> platformTiles_;
        std::vector<ItemTile_t> itemTiles_;
        std::shared_ptr<RenderData_t> renderData_ = nullptr;
        BoardBackground background_;
        TileManager moveTexture_;
        TileHighlight tileHighlight_;

        void UpdatePlatforms();
        void UpdateItems();
        void UpdateMoves();

        void DrawWalls();
        void DrawPlatforms();
        void DrawItems();
        void DrawMoves();

        Coord_t ConvertCoordToPixel(const Coord_t& boardPos);

        public:
        Board();
        explicit Board(const std::shared_ptr<RenderData_t>& renderData);

        void Draw();
    };
} // namespace GUI

#endif /* BB906A41_1129_4933_BDEE_05B69E639647 */
