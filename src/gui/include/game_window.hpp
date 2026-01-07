#ifndef FF3F9D0C_0671_4E5D_BE68_0B1A5D720D85
#define FF3F9D0C_0671_4E5D_BE68_0B1A5D720D85

#include <memory>
#include <mutex>
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include "board.hpp"
#include "controls.hpp"
#include "gui_data.hpp"
#include "item_counter.hpp"
#include "texture_manager.hpp"

extern std::mutex GuiDataMutex;

namespace GUI {
    class GameWindow {
        windowPtr window_;
        std::shared_ptr<RenderData_t> renderData_ = nullptr;
        std::unique_ptr<SDL_Event> eventHandler_;

        Board board_;
        Controls controls_;
        ItemCounter itemCounter_;
        bool isRunning_ = true;

        void RenderLoop();
        void EventLoop();
        void Render();
        void InitialiseNewBoard();

        public:
        explicit GameWindow(std::unique_ptr<GuiData>& guiData);

        bool GetRunning();
    };
} // namespace GUI

#endif /* FF3F9D0C_0671_4E5D_BE68_0B1A5D720D85 */
