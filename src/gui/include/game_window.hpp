#ifndef FF3F9D0C_0671_4E5D_BE68_0B1A5D720D85
#define FF3F9D0C_0671_4E5D_BE68_0B1A5D720D85

#include <memory>
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include "board.hpp"
#include "controls.hpp"
#include "gui_data.hpp"
#include "item_counter.hpp"
#include "texture_manager.hpp"

namespace GUI {
    class GameWindow {
        windowPtr window_;
        std::shared_ptr<RenderData_t> renderData_;
        std::unique_ptr<SDL_Event> eventHandler_;

        Board board_ = Board(nullptr);
        Controls controls_ = Controls(nullptr);
        ItemCounter itemCounter_ = ItemCounter(nullptr);
        bool isRunning_;

        bool MainLoop();
        void Draw();
        // void Free();
        void Render();

        public:
        explicit GameWindow(std::unique_ptr<GuiData> guiData);

        void InitialiseNewBoard();
    };
} // namespace GUI

#endif /* FF3F9D0C_0671_4E5D_BE68_0B1A5D720D85 */
