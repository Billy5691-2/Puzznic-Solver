#include "../../include/GUI/window.hpp"


//SDL 2 Guides

//https://github.com/Candyris/Chess_SDL2-linux/blob/main/%2303-DrawPieces/src/Game.cpp
//https://www.youtube.com/watch?v=39hWcYu-0vY&list=PLtrnQ655KFotSI7VrzFUdMwZN-3IBf3EM&index=3
//https://lazyfoo.net/tutorials/SDL/index.php


namespace GUI {

    /*
    Constructor for Window class
    */
    Window::Window(const char* title, board board_data, std::vector<platform> platform_list) {
        init();
        m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_PRESENTVSYNC);
        m_Board = new Board(m_Renderer);
        tile_size = m_Board->getTileSize();        
        
        reset_board(board_data);
        reset_platform(platform_list);

        //Testing variables
        m_Tile = new Tiles(m_Renderer, RED_ITEM, tile_size);
        std::cout << "Constructor success";
        m_Tile->setPosition(100, 100);

    }

    Window::~Window() {
        delete_board();
        delete_platforms();
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

    void Window::reset_board(board board_data){
        for(int x = 0; x < BOARD_SIZE; x++) {
            for(int y = 0; y < BOARD_SIZE; y++) {
                tile tile_type = board_data.board[x][y];
                char* file_path;

                if (tile_type.wall){

                    switch (tile_type.wall)
                        {
                    case 1:
                        file_path = EXTERIOR_WALL;
                        break;
                    
                    case 2:
                        file_path = FLOOR_WALL;
                        break;

                    case 3:
                        file_path = LEDGE_WALL;
                        break;
                    
                    case 4:
                        file_path = INTERIOR_WALL;
                        break;

                    default:
                        std::cout << "Error with wall type assignment\n";
                        break;
                    }
                    Tiles* temp = new Tiles(m_Renderer, file_path, tile_size);
                    temp->setPosition(x, y);
                    base_tiles.push_back(temp);
                }
                
            }
        }
    }
    void Window::reset_platform(std::vector<platform> platform_list){
        for (int i=0; i<platform_list.size(); i++){
            char* file_path;

            switch (platform_list[i].plane){
                case HORIZONTAL:
                    file_path = RIGHT_PLATFORM;
                    break;

                case VERTICAL:
                    file_path = UP_PLATFORM;
                    break;
                
                default:
                    std::cout << "Platform display error\n";
                    break;
            }

            Tiles* temp = new Tiles(m_Renderer, file_path, tile_size);
            temp->setPosition(platform_list[i].pos.x, platform_list[i].pos.y);
            platform_tiles.push_back(temp);
        }
    }
    void Window::reset_items(std::map<position, int> item_list){
        std::map<position, int>::iterator it;
        for (it = item_list.begin(); it != item_list.end(); it++){
            char* file_path;
            switch (it->second) {
                case RED:
                    file_path = RED_ITEM;
                    break;
                
                case BLUE:
                    file_path = BLUE_ITEM;
                    break;
                
                case GREEN:
                    file_path = GREEN_ITEM;
                    break;
                
                case PINK:
                    file_path = PINK_ITEM;
                    break;

                case PURPLE:
                    file_path = PURPLE_ITEM;
                    break;
                
                case CYAN:
                    file_path = CYAN_ITEM;
                    break;
                
                case BROWN:
                    file_path = BROWN_ITEM;
                    break;
                
                case ORANGE:
                    file_path = ORANGE_ITEM;
                    break;
                
                case YELLOW:
                    file_path = YELLOW_ITEM;
                    break;
                
                default:
                    std::cout << "Error in item texture assignment";
                    break;
            }
            Tiles* temp = new Tiles(m_Renderer, file_path, tile_size);
            temp->setPosition(it->first.x, it->first.y);
            item_tiles.push_back(temp);
        }

    }

    void Window::delete_board(){
        for (int i = base_tiles.size()-1; i >= 0; i--){
            delete base_tiles[i];
        }
        base_tiles.clear();
    }
    void Window::delete_platforms(){
        for (int i = platform_tiles.size()-1; i >= 0; i--){
            delete platform_tiles[i];
        }
        platform_tiles.clear();
    }
    void Window::delete_items(){
        for (int i = item_tiles.size(); i >= 0; i--){
            delete item_tiles[i];
        }
        item_tiles.clear();
    }

    void Window::reset(board board_data, std::vector<platform> platform_list){
        delete_board();
        delete_platforms();

        reset_board(board_data);
        reset_platform(platform_list);
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

    void Window::render(std::map<position, int> item_list) {
        SDL_SetRenderDrawColor(m_Renderer, 128, 0, 255, 255);
        SDL_RenderClear(m_Renderer);
        m_Board->drawBoard();

        render_board();
        render_platforms();
        
        render_items(item_list);

        SDL_RenderPresent(m_Renderer);
        delete_items();
    }

    void Window::render_board() {
        for (int i=0; i<base_tiles.size(); i++){
            base_tiles[i]->draw();
        }
    }

    void Window::render_platforms(){
        for (int i=0; i<platform_tiles.size(); i++){
            platform_tiles[i]->draw();
        }
    }

    void Window::render_items(std::map<position, int> item_list){
        reset_items(item_list);
        for (int i=0; i<platform_tiles.size(); i++){
            platform_tiles[i]->draw();
        }

    }









}
