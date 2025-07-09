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

        m_Font_ = TTF_OpenFont("../assets/fonts/OpenSans-Regular.ttf", 30);
        m_TextColour_ = {255, 255, 255};

        if (m_Font_ == NULL) { 
            std::cout << "Opening font failed!\n";
        }

        

        m_Board = new BoardBackground(m_Renderer);
        tileSize_ = m_Board->GetTileSize();

        m_Count = new ItemCounter(m_Renderer, m_Font_, m_TextColour_,
            tileSize_, item_paths_array);
            
        m_Controls = new Controls(m_Renderer, m_Font_, m_TextColour_, tileSize_);
        
        ResetBoard(board_data);
        ResetPlatform(platform_list);


        movePair_.original.x = 0;
        movePair_.original.y = 0;
        movePair_.updated.x = 0;
        movePair_.updated.y = 0;

        std::cout << "Constructor success\n";
    }

    Window::~Window() {
        DeleteBoard();
        DeletePlatforms();
        delete m_Event;
        delete m_Board;
        delete m_Count;
        delete m_Controls;
        SDL_DestroyRenderer(m_Renderer);
        SDL_DestroyWindow(m_Window);

        TTF_CloseFont(m_Font_);
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

    bool Window::IsRunning() const {
        return m_Running;
    }

    void Window::PollEvent() {
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
                                grid_x = x / tileSize_;
                                grid_y = y / tileSize_;
                                std::cout << "X " << grid_x << " Y " << grid_y << "\n";
                                highlightChange_ = true;
                                movePair_.original.x = movePair_.updated.x;
                                movePair_.original.y = movePair_.updated.y;
                                movePair_.updated.x = grid_x;
                                movePair_.updated.y = grid_y;


                            } else if (x > WINDOW_RIGHT_OFFSET) {
                                m_Controls->HandleClick(x, y);
                            }
                    }
            }
        }
    }

    void Window::DrawHighlight(){
        SDL_Rect _block;
        _block.x = (movePair_.updated.x* tileSize_) + WINDOW_LEFT;
        _block.y = movePair_.updated.y* tileSize_;
        _block.w = _block.h = tileSize_ - 1;
        SDL_SetRenderDrawColor(m_Renderer, 225, 225, 85, 0);
        SDL_RenderDrawRect(m_Renderer, &_block);
    }

    bool Window::Update() {
        bool change = false;
        if (m_Controls->GetChangeLvl()) { 
            change = true; 
            levelChange_ = true;

        }
        if (m_Controls->GetStartSolver()){
            change = true;
            solveChange_ = true;

        }
        if (highlightChange_){
            change = true;
        }
        return change;

    }

    move Window::GetMove(){
        highlightChange_ = false;
        return movePair_;
    }

    bool Window::GetHightlightChange(){ return highlightChange_; }

    bool Window::ChangeLevelState(){ return levelChange_; }
    std::string Window::GetLvlFilename(){
        levelChange_ = false;
        return m_Controls->GetLvlFilename();
    }

    bool Window::StartSolverState(){ 
        if (solveChange_) {
            solveChange_ = false;
            return true;
        } else {
            return false;
        }
    }

    void Window::Render(std::map<position, int> item_list, std::vector<platform> platform_list, 
        std::array<int, COLOURS> item_count, std::vector<position> move_list) {
        SDL_SetRenderDrawColor(m_Renderer, 128, 0, 255, 255);
        SDL_RenderClear(m_Renderer);
        m_Board->DrawBackground();

        m_Count->DrawTiles();
        m_Count->DrawText(item_count);

        m_Controls->Render();

        RenderBoard();
        RenderPlatforms(platform_list);
        RenderItems(item_list);
        RenderMoves(move_list);

        DrawHighlight();

        SDL_RenderPresent(m_Renderer);
        DeleteItems();
        DeleteMoves();
        m_Count->Free();
        m_Controls->Free();
    }

    void Window::RenderBoard() {
        for (int i=0; i<baseTilesVec_.size(); i++){
            baseTilesVec_[i]->Draw();
        }
    }
    void Window::RenderPlatforms(std::vector<platform> platform_list) {
        for (int i=0; i<platformTilesVec_.size(); i++){
            platformTilesVec_[i]->SetPosition(GridToPixel(platform_list[i].pos));
            platformTilesVec_[i]->Draw();
        }
    }
    void Window::RenderItems(std::map<position, int> item_list){
        ResetItems(item_list);
        for (int i=0; i<itemTiles_.size(); i++){
            itemTiles_[i]->Draw();
        }
    }
    void Window::RenderMoves(std::vector<position> move_list){
        ResetMoves(move_list);
        for (int i=0; i<move_list.size(); i++){
            moveTiles_[i]->Draw();
        }
    }

    position Window::GridToPixel(position pos) {
        return GridToPixel(pos.x, pos.y);
    }
    position Window::GridToPixel(int x, int y) {
        position pixel_pos;
        pixel_pos.x = WINDOW_LEFT + (x * tileSize_);
        pixel_pos.y = y * tileSize_;
        return pixel_pos;
    }

    void Window::ResetBoard(board board_data){
        for(int x = 0; x < kBoardSize; x++) {
            for(int y = 0; y < kBoardSize; y++) {
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
                    Tiles* temp = new Tiles(m_Renderer, file_path, tileSize_);
                    temp->SetPosition(GridToPixel(x, y));
                    baseTilesVec_.push_back(temp);
                }
                
            }
        }
    }
    void Window::ResetPlatform(std::vector<platform> platform_list){
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

            Tiles* temp = new Tiles(m_Renderer, file_path, tileSize_);
            temp->SetPosition(GridToPixel(platform_list[i].pos));
            //temp->setPosition(platform_list[i].pos.x, platform_list[i].pos.y);
            platformTilesVec_.push_back(temp);
        }
    }
    void Window::ResetItems(std::map<position, int> item_list){
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
            Tiles* temp = new Tiles(m_Renderer, file_path, tileSize_);
            temp->SetPosition(GridToPixel(it->first));
            //temp->setPosition(it->first.x, it->first.y);
            itemTiles_.push_back(temp);
        }

    }
    void Window::ResetMoves(std::vector<position> move_list){
        for (int i=0; i<move_list.size(); i++){
            Tiles* temp = new Tiles(m_Renderer, MOVE_MARKER_PATH, tileSize_);
            temp->SetPosition(GridToPixel(move_list[i]));
            moveTiles_.push_back(temp);
        }
    }

    void Window::Reset(board board_data, std::vector<platform> platform_list){
        DeleteBoard();
        DeletePlatforms();

        ResetBoard(board_data);
        ResetPlatform(platform_list);
    }

    void Window::DeleteBoard(){
        for (int i = baseTilesVec_.size()-1; i >= 0; i--){
            delete baseTilesVec_[i];
        }
        baseTilesVec_.clear();
    }
    void Window::DeletePlatforms(){
        for (int i = platformTilesVec_.size()-1; i >= 0; i--){
            delete platformTilesVec_[i];
        }
        platformTilesVec_.clear();
    }
    void Window::DeleteItems(){
        for (int i = itemTiles_.size()-1; i >= 0; i--){
            delete itemTiles_[i];
        }
        itemTiles_.clear();
    }
    void Window::DeleteMoves(){
        for (int i = moveTiles_.size()-1; i >= 0; i--){
            delete moveTiles_[i];
        }
        moveTiles_.clear();
    }


}
