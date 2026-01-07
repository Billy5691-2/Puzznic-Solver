#ifndef ABABD979_3D8F_4D06_8428_9E7D26F0D2C4
#define ABABD979_3D8F_4D06_8428_9E7D26F0D2C4

#include <array>
#include <map>
#include <memory>
#include <mutex>
#include <vector>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

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

    struct Level_t {
        int stage = 1;
        int subStage = 1;
    };

    extern std::mutex GuiDataMutex;

    class GuiData {
        std::string basePath_;

        Level_t level_;
        GuiMove_t move_;
        bool changeLevel_ = false;
        bool resetBoard_ = false;
        bool startSolver_ = false;

        // Data from game
        std::array<int, NUMBER_OF_ITEMS> itemCount_ = {-1};
        std::vector<Coord_t> availableMoves_;
        Board_t board_;

        public:
        GuiData();
        GuiData& operator=(GuiData&& other) noexcept = default;
        ~GuiData() = default;
        GuiData(const GuiData&) = delete;
        GuiData(const GuiData&&) = delete;
        GuiData& operator=(const GuiData& other) = default;

        // Game Setters
        void SetItemCount(const std::array<int, NUMBER_OF_ITEMS>& itemCount);
        void SetAvailableMoves(const std::vector<Coord_t>& moves);
        void SetBoard(const Board_t& board);

        // Value Setters
        void UpdateStage(int change);
        void UpdateSubStage(int change);
        void SetMovePos(const Coord_t& pos);
        void SetMoveItem(const int id);
        void SetResetBoard(bool flag);
        void SetChangeLevel(bool state);
        void SetSolverStart(bool state);
        void ResetMove();


        // Getters
        bool GetChangeLevelState();
        bool GetSolverStartState();
        const Item_t& GetMoveHighlight();
        const Level_t& GetLevel();
        const std::string GetLevelPath();
        const std::string& GetBasePath();
        const GuiMove_t GetMove();

        // Game Getters
        bool GetResetBoard();
        const std::array<int, NUMBER_OF_ITEMS>& GetItemCount();
        const std::vector<Platform_t>& GetPlatforms();
        const std::vector<Item_t>& GetItems();
        const std::vector<Coord_t>& GetMoves();
        const std::array<std::array<WallType, BOARD_SIZE>, BOARD_SIZE>& GetWalls();
    };

    struct RenderData_t {
        std::unique_ptr<GuiData> data = nullptr;
        TextureManager textures = TextureManager();
        std::shared_ptr<SDL_Renderer> renderer = nullptr;
        fontPtr font = nullptr; // fontPtr(TTF_OpenFont("../assets/fonts/OpenSans-Regular.ttf", 30))
    };
}; // namespace GUI

#endif /* ABABD979_3D8F_4D06_8428_9E7D26F0D2C4 */
