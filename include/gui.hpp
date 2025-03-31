#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdlib.h>
//#include "structs.hpp"

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 900;

class Gui {
    SDL_Event* m_Event;
    SDL_Renderer* m_Renderer;
    SDL_Window* m_Window;
    bool m_Running = false;

    void init();

    public:
        Gui(const char* title);
        ~Gui();

        bool isRunning() const;
        void pollEvent();
        void update();
        void render();

};