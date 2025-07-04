#include "../../include/GUI/window.hpp"


//SDL 2 Guides

//https://github.com/Candyris/Chess_SDL2-linux/blob/main/%2303-DrawPieces/src/Game.cpp
//https://www.youtube.com/watch?v=39hWcYu-0vY&list=PLtrnQ655KFotSI7VrzFUdMwZN-3IBf3EM&index=3
//https://lazyfoo.net/tutorials/SDL/index.php


const char* RED_ITEM_PATH = RED_ITEM;
const char* BLUE_ITEM_PATH = BLUE_ITEM;
const char* GREEN_ITEM_PATH = GREEN_ITEM;
const char* PINK_ITEM_PATH = PINK_ITEM;
const char* PURPLE_ITEM_PATH = PURPLE_ITEM;
const char* CYAN_ITEM_PATH = CYAN_ITEM;
const char* BROWN_ITEM_PATH = BROWN_ITEM;
const char* ORANGE_ITEM_PATH = ORANGE_ITEM;
const char* YELLOW_ITEM_PATH = YELLOW_ITEM;

const char* EXTERIOR_WALL_PATH = EXTERIOR_WALL;
const char* FLOOR_WALL_PATH = FLOOR_WALL;
const char* LEDGE_WALL_PATH = LEDGE_WALL;
const char* INTERIOR_WALL_PATH = INTERIOR_WALL;
const char* GREEN_WALL_PATH = GREEN_WALL;

const char* UP_PLATFORM_PATH = UP_PLATFORM;
const char* DOWN_PLATFORM_PATH = DOWN_PLATFORM;
const char* RIGHT_PLATFORM_PATH = RIGHT_PLATFORM;
const char* LEFT_PLATFORM_PATH = LEFT_PLATFORM;

const char* MOVE_MARKER_PATH = MOVE_MARKER;

std::array<const char*, COLOURS> item_paths_array = {
    RED_ITEM_PATH, 
    BLUE_ITEM_PATH, 
    GREEN_ITEM_PATH,
    PINK_ITEM_PATH,
    PURPLE_ITEM_PATH,
    CYAN_ITEM_PATH,
    BROWN_ITEM_PATH,
    ORANGE_ITEM_PATH,
    YELLOW_ITEM_PATH
};


namespace GUI {

    /*
    Constructor for Window class
    */
    Window::Window(const char* title, board board_data, std::vector<platform> platform_list) {
        init();

        m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_PRESENTVSYNC);

        m_Font = TTF_OpenFont("../assets/fonts/OpenSans-Regular.ttf", 30);
        m_Txt_Colour = {255, 255, 255};

        if (m_Font == NULL) { 
            std::cout << "Opening font failed!\n";
        }

        

        m_Board = new Board(m_Renderer);
        tile_size = m_Board->getTileSize();

        m_Count = new ItemCounter(m_Renderer, m_Font, m_Txt_Colour,
            tile_size, item_paths_array);
            
        m_Controls = new Controls(m_Renderer, m_Font, m_Txt_Colour, tile_size);
        
        reset_board(board_data);
        reset_platform(platform_list);


        move_pair.original.x = 0;
        move_pair.original.y = 0;
        move_pair.updated.x = 0;
        move_pair.updated.y = 0;

        std::cout << "Constructor success\n";
    }

    Window::~Window() {
        delete_board();
        delete_platforms();
        delete m_Event;
        delete m_Board;
        delete m_Count;
        delete m_Controls;
        SDL_DestroyRenderer(m_Renderer);
        SDL_DestroyWindow(m_Window);

        TTF_CloseFont(m_Font);
        TTF_Quit();

    }

    //Initialises values
    void Window::init() {
        TTF_Init();
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

                //SDL window is closed
                case SDL_QUIT:
                    m_Running = false;
                    break;
                
                // A mouse button is pressed
                case SDL_MOUSEBUTTONDOWN:
                    switch (m_Event->button.button) {
                        case SDL_BUTTON_LEFT:
                            int x, y;
                            SDL_GetMouseState(&x, &y);
                            if (x > WINDOW_LEFT && x < WINDOW_RIGHT_OFFSET) {
                                x = x - WINDOW_LEFT;
                                int grid_x, grid_y;
                                grid_x = x / tile_size;
                                grid_y = y / tile_size;
                                std::cout << "X " << grid_x << " Y " << grid_y << "\n";
                                highlight_change = true;
                                move_pair.original.x = move_pair.updated.x;
                                move_pair.original.y = move_pair.updated.y;
                                move_pair.updated.x = grid_x;
                                move_pair.updated.y = grid_y;


                            } else if (x > WINDOW_RIGHT_OFFSET) {
                                m_Controls->handle_click(x, y);
                            }
                    }
            }
        }
    }

    void Window::draw_highlight(){
        SDL_Rect _block;
        _block.x = (move_pair.updated.x* tile_size) + WINDOW_LEFT;
        _block.y = move_pair.updated.y* tile_size;
        _block.w = _block.h = tile_size - 1;
        SDL_SetRenderDrawColor(m_Renderer, 225, 225, 85, 0);
        SDL_RenderDrawRect(m_Renderer, &_block);
    }

    bool Window::update() {
        bool change = false;
        if (m_Controls->change_level()) { 
            change = true; 
            level_change = true;

        }
        if (m_Controls->start_solver()){
            change = true;
            solve_change = true;

        }
        if (highlight_change){
            change = true;
        }
        return change;

    }

    move Window::get_move(){
        highlight_change = false;
        return move_pair;
    }

    bool Window::get_highlight_change(){ return highlight_change; }

    bool Window::change_level_state(){ return level_change; }
    std::string Window::new_level_file(){
        level_change = false;
        return m_Controls->new_level_file();
    }

    bool Window::start_solver_state(){ 
        if (solve_change) {
            solve_change = false;
            return true;
        } else {
            return false;
        }
    }

    void Window::render(std::map<position, int> item_list, std::vector<platform> platform_list, 
        std::array<int, COLOURS> item_count, std::vector<position> move_list) {
        SDL_SetRenderDrawColor(m_Renderer, 128, 0, 255, 255);
        SDL_RenderClear(m_Renderer);
        m_Board->drawBoard();

        m_Count->draw_tiles();
        m_Count->draw_text(item_count);

        m_Controls->render();

        render_board();
        render_platforms(platform_list);
        render_items(item_list);
        render_moves(move_list);

        draw_highlight();

        SDL_RenderPresent(m_Renderer);
        delete_items();
        delete_moves();
        m_Count->free_text();
        m_Controls->free();
    }

    void Window::render_board() {
        for (int i=0; i<base_tiles.size(); i++){
            base_tiles[i]->draw();
        }
    }
    void Window::render_platforms(std::vector<platform> platform_list) {
        for (int i=0; i<platform_tiles.size(); i++){
            platform_tiles[i]->setPosition(grid_to_pixel(platform_list[i].pos));
            platform_tiles[i]->draw();
        }
    }
    void Window::render_items(std::map<position, int> item_list){
        reset_items(item_list);
        for (int i=0; i<item_tiles.size(); i++){
            item_tiles[i]->draw();
        }
    }
    void Window::render_moves(std::vector<position> move_list){
        reset_moves(move_list);
        for (int i=0; i<move_list.size(); i++){
            move_tiles[i]->draw();
        }
    }

    position Window::grid_to_pixel(position pos) {
        return grid_to_pixel(pos.x, pos.y);
    }
    position Window::grid_to_pixel(int x, int y) {
        position pixel_pos;
        pixel_pos.x = WINDOW_LEFT + (x * tile_size);
        pixel_pos.y = y * tile_size;
        return pixel_pos;
    }

    void Window::reset_board(board board_data){
        for(int x = 0; x < BOARD_SIZE; x++) {
            for(int y = 0; y < BOARD_SIZE; y++) {
                tile tile_type = board_data.board[x][y];
                const char* file_path;

                if (tile_type.wall){

                    switch (tile_type.wall)
                        {
                    case 1:
                        file_path = EXTERIOR_WALL_PATH;
                        break;
                    
                    case 2:
                        file_path = FLOOR_WALL_PATH;
                        break;

                    case 3:
                        file_path = LEDGE_WALL_PATH;
                        break;
                    
                    case 4:
                        file_path = INTERIOR_WALL_PATH;
                        break;

                    default:
                        std::cout << "Error with wall type assignment\n";
                        break;
                    }
                    Tiles* temp = new Tiles(m_Renderer, file_path, tile_size);
                    temp->setPosition(grid_to_pixel(x, y));
                    base_tiles.push_back(temp);
                }
                
            }
        }
    }
    void Window::reset_platform(std::vector<platform> platform_list){
        for (int i=0; i<platform_list.size(); i++){
            const char* file_path;

            switch (platform_list[i].plane){
                case HORIZONTAL:
                    file_path = RIGHT_PLATFORM_PATH;
                    break;

                case VERTICAL:
                    file_path = UP_PLATFORM_PATH;
                    break;
                
                default:
                    std::cout << "Platform display error\n";
                    break;
            }

            Tiles* temp = new Tiles(m_Renderer, file_path, tile_size);
            temp->setPosition(grid_to_pixel(platform_list[i].pos));
            //temp->setPosition(platform_list[i].pos.x, platform_list[i].pos.y);
            platform_tiles.push_back(temp);
        }
    }
    void Window::reset_items(std::map<position, int> item_list){
        std::map<position, int>::iterator it;
        for (it = item_list.begin(); it != item_list.end(); it++){
            const char* file_path;
            switch (it->second) {
                case RED:
                    file_path = RED_ITEM_PATH;
                    break;
                
                case BLUE:
                    file_path = BLUE_ITEM_PATH;
                    break;
                
                case GREEN:
                    file_path = GREEN_ITEM_PATH;
                    break;
                
                case PINK:
                    file_path = PINK_ITEM_PATH;
                    break;

                case PURPLE:
                    file_path = PURPLE_ITEM_PATH;
                    break;
                
                case CYAN:
                    file_path = CYAN_ITEM_PATH;
                    break;
                
                case BROWN:
                    file_path = BROWN_ITEM_PATH;
                    break;
                
                case ORANGE:
                    file_path = ORANGE_ITEM_PATH;
                    break;
                
                case YELLOW:
                    file_path = YELLOW_ITEM_PATH;
                    break;
                
                default:
                    std::cout << "Error in item texture assignment";
                    break;
            }
            Tiles* temp = new Tiles(m_Renderer, file_path, tile_size);
            temp->setPosition(grid_to_pixel(it->first));
            //temp->setPosition(it->first.x, it->first.y);
            item_tiles.push_back(temp);
        }

    }
    void Window::reset_moves(std::vector<position> move_list){
        for (int i=0; i<move_list.size(); i++){
            Tiles* temp = new Tiles(m_Renderer, MOVE_MARKER_PATH, tile_size);
            temp->setPosition(grid_to_pixel(move_list[i]));
            move_tiles.push_back(temp);
        }
    }

    void Window::reset(board board_data, std::vector<platform> platform_list){
        delete_board();
        delete_platforms();

        reset_board(board_data);
        reset_platform(platform_list);
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
        for (int i = item_tiles.size()-1; i >= 0; i--){
            delete item_tiles[i];
        }
        item_tiles.clear();
    }
    void Window::delete_moves(){
        for (int i = move_tiles.size()-1; i >= 0; i--){
            delete move_tiles[i];
        }
        move_tiles.clear();
    }


}
