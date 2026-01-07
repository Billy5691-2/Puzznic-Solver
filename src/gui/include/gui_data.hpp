#ifndef ABABD979_3D8F_4D06_8428_9E7D26F0D2C4
#define ABABD979_3D8F_4D06_8428_9E7D26F0D2C4

#include <array>
#include <map>
#include <memory>
#include <mutex>
#include <vector>

#include "SDL2/SDL_render.h"
#include "SDL2/SDL_ttf.h"
#include "constants.hpp"
#include "enums.hpp"
#include "structs.hpp"
#include "texture_manager.hpp"

namespace GUI {

    struct SDLWindowDeleter {
        void operator()(SDL_Window* window) const {
            if (window) {
                SDL_DestroyWindow(window);
            }
        }
    };
    using windowPtr = std::unique_ptr<SDL_Window, SDLWindowDeleter>;

    struct TTF_FontDeleter {
        void operator()(TTF_Font* font) const {
            if (font) {
                TTF_CloseFont(font);
            }
        }
    };
    using fontPtr = std::unique_ptr<TTF_Font, TTF_FontDeleter>;

    struct GuiMove_t {
        Move_t move;
        bool moveMade = false;
    };

    class GuiData {
        std::mutex dataMutex_;
        std::unique_ptr<int> currLevel_ = nullptr;
        std::unique_ptr<int> currStage_ = nullptr;
        int newLevel_ = 0;
        int newStage_ = 0;
        bool changeLevel_ = false;
        bool resetBoard_ = false;
        std::unique_ptr<GuiMove_t> move_ = nullptr;

        // Data from game
        std::unique_ptr<const std::array<int, NUMBER_OF_ITEMS>> itemCount_ = nullptr;
        std::unique_ptr<const std::map<int, Platform>> platforms_ = nullptr;
        std::unique_ptr<const std::map<int, Item>> items_ = nullptr;
        std::unique_ptr<const std::vector<Coord>> availableMoves_ = nullptr;
        std::unique_ptr<const std::array<std::array<WallType, BOARD_SIZE>, BOARD_SIZE>> walls_ = nullptr;

        public:
        GuiData();

        // Pointer Setters
        void SetItemCountPtr(std::unique_ptr<const std::array<int, NUMBER_OF_ITEMS>> itemCount);
        void SetItemsPtr(std::unique_ptr<const std::map<int, Item>> items);
        void SetPlatformsPtr(std::unique_ptr<const std::map<int, Platform>> platforms);
        void SetBoardPtr(std::unique_ptr<const std::array<std::array<WallType, BOARD_SIZE>, BOARD_SIZE>> walls);
        void SetAvailableMovesPtr(std::unique_ptr<const std::vector<Coord>> moves);

        void SetMovePtr(std::unique_ptr<GuiMove_t> move);
        void SetLevelPtr(std::unique_ptr<int> level);
        void SetStagePtr(std::unique_ptr<int> stage);

        // Value Setters
        void UpdateLevel(int change);
        void UpdateStage(int change);
        void SetNewLevel();
        void SetMovePos(const Coord& pos);
        void SetMoveItem(const int id);
        void SetResetBoard(bool flag);
        void SetChangeLevel(bool state);

        // Getters
        bool GetResetBoard();
        bool GetChangeLevelState();
        const Item GetMoveHighlight();
        int GetLevel();
        int GetStage();
        const std::array<int, NUMBER_OF_ITEMS> GetItemCount();
        const std::map<int, Platform> GetPlatforms();
        const std::map<int, Item> GetItems();
        const std::vector<Coord> GetMoves();
        const std::array<std::array<WallType, BOARD_SIZE>, BOARD_SIZE> GetWalls();
    };

    struct RenderData_t {
        std::unique_ptr<GuiData> data;
        TextureManager textures = TextureManager(nullptr);
        std::shared_ptr<SDL_Renderer> renderer = nullptr;
        fontPtr font = fontPtr(TTF_OpenFont("../assets/fonts/OpenSans-Regular.ttf", 30));
    };
}; // namespace GUI

#endif /* ABABD979_3D8F_4D06_8428_9E7D26F0D2C4 */
