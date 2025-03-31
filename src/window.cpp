#include "../include/window.hpp"
namespace GUI {
    Window::Window(const char* title, position board_data) {
        init();
        SDL_Window* m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        SDL_Renderer* m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_PRESENTVSYNC);
        if (m_Renderer == NULL){
            std::cout << "Error";
        }
        m_Board = new Board(board_data, m_Renderer);

    }

    Window::~Window() {
        delete m_Event;
        delete m_Board;
        SDL_DestroyRenderer(m_Renderer);
        SDL_DestroyWindow(m_Window);

    }

    void Window::init() {
        m_Event = new SDL_Event;
        m_Window = NULL;
        m_Renderer = NULL;
        m_Running = true;


    }


    bool Window::isRunning() const {
        return m_Running;
    }

    void Window::pollEvent() {
        while (SDL_PollEvent(m_Event)) {
            switch (m_Event->type) {
                case SDL_QUIT:
                    m_Running = false;
                    break;
            }
        }
    }

    void Window::update() {

    }

    void Window::render() {
        SDL_SetRenderDrawColor(m_Renderer, 128, 128, 20, 255);
        SDL_RenderClear(m_Renderer);
        m_Board->drawBoard();
        //SDL_RenderCopy(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect *srcrect, const SDL_Rect *dstrect);

        SDL_RenderPresent(m_Renderer);
    }
}