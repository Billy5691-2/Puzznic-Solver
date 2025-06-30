#include "../../include/GUI/window.hpp"


//SDL 2 Guides

//https://github.com/Candyris/Chess_SDL2-linux/blob/main/%2303-DrawPieces/src/Game.cpp
//https://www.youtube.com/watch?v=39hWcYu-0vY&list=PLtrnQ655KFotSI7VrzFUdMwZN-3IBf3EM&index=3
//https://lazyfoo.net/tutorials/SDL/index.php


namespace GUI {

    /*
    Constructor for Window class
    */
    Window::Window(const char* title, board board_data) {
        init();
        m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_PRESENTVSYNC);
        m_Board = new Board(m_Renderer);
        int tile_size = m_Board->getTileSize();        

        //Testing variables
        m_Tile = new Tiles(m_Renderer, RED_ITEM, tile_size);
        std::cout << "Constructor success";
        m_Tile->setPosition(100, 100);



    }

    Window::~Window() {
        delete m_Event;
        delete m_Board;
        delete m_Tile;
        SDL_DestroyRenderer(m_Renderer);
        SDL_DestroyWindow(m_Window);

    }

    //Initialises values
    void Window::init() {
        m_Event = new SDL_Event;
        m_Window = NULL;
        m_Renderer = NULL;
        m_Running = true;
        m_Is_Selected = false;

    }


    bool Window::isRunning() const {
        return m_Running;
    }

    void Window::pollEvent() {
        while (SDL_PollEvent(m_Event)) {
            switch (m_Event->type) {

                //SDL window is closed
                case SDL_QUIT:
                    m_Running = false;
                    break;
                
                // A mouse button is pressed
                case SDL_MOUSEBUTTONDOWN:
                    switch (m_Event->button.button) {
                        case SDL_BUTTON_LEFT:
                            m_Is_Selected = true;
                            int x, y;
                            SDL_GetMouseState(&x, &y);
                            m_Tile->setPosition(x, y);
                    }


            }
        }
    }

    void Window::update() {
        if (m_Is_Selected) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            x -= 35;
            y -= 35;
            m_Tile->setPosition(x, y);
        }

    }

    void Window::render_start() {
        SDL_SetRenderDrawColor(m_Renderer, 128, 0, 255, 255);
        SDL_RenderClear(m_Renderer);
        m_Board->drawBoard();
    }

    void Window::render_board() {
        
    }

    void render_platforms(std::vector<platform> platform_list){

    }

    void render_items(std::map<position, int> item_list){

    }

    void Window::render_finish() {
        SDL_RenderPresent(m_Renderer);
    }







}
