#include "../include/gui.hpp"

Gui::Gui(const char* title) {
    init();
    SDL_Window* m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_PRESENTVSYNC);

}

Gui::~Gui() {
    delete m_Event;
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);

}

void Gui::init() {
    m_Event = new SDL_Event;
    m_Window = NULL;
    m_Renderer = NULL;
    m_Running = true;


}


bool Gui::isRunning() const {
    return m_Running;
}

void Gui::pollEvent() {
    while (SDL_PollEvent(m_Event)) {
        switch (m_Event->type) {
            case SDL_QUIT:
                m_Running = false;
                break;
        }
    }
}

void Gui::update() {

}

void Gui::render() {
    SDL_SetRenderDrawColor(m_Renderer, 128, 128, 20, 128);
    SDL_RenderClear(m_Renderer);
    SDL_RenderPresent(m_Renderer);
}