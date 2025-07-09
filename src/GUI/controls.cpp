#include "../../include/GUI/controls.hpp"

//const char* UP_ARROW_PATH = UP_ARROW;
//const char* DOWN_ARROW_PATH = DOWN_ARROW;
const char* UP_ARROW_PATH = UP_PLATFORM;
const char* DOWN_ARROW_PATH = DOWN_PLATFORM;

//const int WINDOW_RIGHT_OFFSET = WINDOW_HEIGHT + WINDOW_LEFT; //Lefthand side of window rightside
//const int WINDOW_RIGHT_SIZE = (WINDOW_WIDTH - WINDOW_HEIGHT) * 0.6; //Lefthand side of window rightside

SDL_Colour active_button = {200, 200, 200};
SDL_Colour inactive_button = {115, 115, 115};
SDL_Colour pressed_button = {180, 180, 180};
SDL_Colour highlight_colour = {65, 185, 205};

const int GAP = 10;




namespace GUI {
    Controls::Controls(SDL_Renderer* p_Renderer, TTF_Font* p_Font, SDL_Colour p_Txt_Colour,
                int p_tile_size) {
        m_Renderer = p_Renderer;
        m_Font_ = p_Font;
        m_TextColour = p_Txt_Colour;
        tileSize_ = p_tile_size;

        upArrowLvl_ = new Tiles(m_Renderer, UP_ARROW_PATH, tileSize_);
        upArrowLvl_->SetPosition(RIGHT_MID - (tileSize_*1.5), GAP);

        upArrowStage_ = new Tiles(m_Renderer, UP_ARROW_PATH, tileSize_);
        upArrowStage_->SetPosition(RIGHT_MID - (tileSize_*1.5), GAP + GAP + tileSize_);

        downArrowLvl_ = new Tiles(m_Renderer, DOWN_ARROW_PATH, tileSize_);
        downArrowLvl_->SetPosition(RIGHT_MID + (tileSize_*0.5), GAP);

        downArrowStage_ = new Tiles(m_Renderer, DOWN_ARROW_PATH, tileSize_);
        downArrowStage_->SetPosition(RIGHT_MID + (tileSize_*0.5), GAP + GAP + tileSize_);
        
        int w, h;
        loadTextSurface_ = TTF_RenderText_Solid(m_Font_, "Load", m_TextColour);
        loadTextTexture_ = SDL_CreateTextureFromSurface(m_Renderer, loadTextSurface_);
        TTF_SizeText(m_Font_, "Load", &w, &h);

        loadTextRect_.x = RIGHT_MID - (w / 2);
        loadTextRect_.y = GAP + ((GAP + tileSize_) * 2);
        loadTextRect_.w = w;
        loadTextRect_.h = h;

        solveTextSurface_ = TTF_RenderText_Solid(m_Font_, "Solve", m_TextColour);
        solveTextTexture_ = SDL_CreateTextureFromSurface(m_Renderer, solveTextSurface_);
        TTF_SizeText(m_Font_, "Solve", &w, &h);

        solveTextRect_.x = RIGHT_MID - (w / 2);
        solveTextRect_.y = GAP + ((GAP + tileSize_) * 3);
        solveTextRect_.w = w;
        solveTextRect_.h = h;

    }

    Controls::~Controls(){
        SDL_FreeSurface(loadTextSurface_);
        SDL_DestroyTexture(loadTextTexture_);
        SDL_FreeSurface(solveTextSurface_);
        SDL_DestroyTexture(solveTextTexture_);
        std::cout << "Controls destroyed\n";
    }

    void Controls::HandleClick(int x, int y){
        if (y > GAP && y < GAP + tileSize_) {
            if (x > RIGHT_MID - (tileSize_*1.5) && x < RIGHT_MID - (tileSize_*0.5)) {
                //Up arrow level
                level_ = CheckNumBounds(level_, 1);
            } else if (x > RIGHT_MID + (tileSize_*0.5) && x < RIGHT_MID + (tileSize_*1.5)){
                //Down arrow level
                level_ = CheckNumBounds(level_, -1);
            }
        } else if (y > GAP + (GAP + tileSize_) && y < GAP + tileSize_ + (GAP + tileSize_)) {
            if (x > RIGHT_MID - (tileSize_*1.5) && x < RIGHT_MID - (tileSize_*0.5)) {
                //Up arrow stage
                stage_ = CheckNumBounds(stage_, 1);
            } else if (x > RIGHT_MID + (tileSize_*0.5) && x < RIGHT_MID + (tileSize_*1.5)){
                //Down arrow stage
                stage_ = CheckNumBounds(stage_, -1);
            }
        } else if (y > GAP + ((GAP + tileSize_) * 2) && 
        y < GAP + tileSize_ + ((GAP + tileSize_) * 2)) {
            if (x > RIGHT_MID - (tileSize_*1.5) && x < RIGHT_MID + (tileSize_*1.5)) {
                loadButtonPressed_ = true;
                //load button
            }
        } else if (y > GAP + ((GAP + tileSize_) * 3) && 
        y < GAP + tileSize_ + ((GAP + tileSize_) * 3)) {
            if (x > RIGHT_MID - (tileSize_*1.5) && x < RIGHT_MID + (tileSize_*1.5)) {
                solveButtonPressed_ = true;
                //solve button
            }
        }
    }

    void Controls::DrawText() {
        SDL_RenderCopy(m_Renderer, loadTextTexture_, NULL, &loadTextRect_);
        SDL_RenderCopy(m_Renderer, solveTextTexture_, NULL, &solveTextRect_);

        std::string temp_str = std::to_string(level_);
        char const *level_char = temp_str.c_str();

        int w, h;
        levelTextSurface_ = TTF_RenderText_Solid(m_Font_, level_char, m_TextColour);
        levelTextTexture_ = SDL_CreateTextureFromSurface(m_Renderer, levelTextSurface_);
        TTF_SizeText(m_Font_, level_char, &w, &h);

        SDL_Rect levelTextRect_;
        levelTextRect_.x = RIGHT_MID - (w / 2);
        levelTextRect_.y = GAP;
        levelTextRect_.w = w;
        levelTextRect_.h = h;

        SDL_RenderCopy(m_Renderer, levelTextTexture_, NULL, &levelTextRect_);
        
        temp_str = std::to_string(stage_);
        char const *stage_char = temp_str.c_str();

        stageTextSurface_ = TTF_RenderText_Solid(m_Font_, stage_char, m_TextColour);
        stageTextTexture_ = SDL_CreateTextureFromSurface(m_Renderer, stageTextSurface_);
        TTF_SizeText(m_Font_, stage_char, &w, &h);

        SDL_Rect stageTextRect_;
        stageTextRect_.x = RIGHT_MID - (w / 2);
        stageTextRect_.y = GAP + (tileSize_ + GAP);
        stageTextRect_.w = w;
        stageTextRect_.h = h;

        SDL_RenderCopy(m_Renderer, stageTextTexture_, NULL, &stageTextRect_);

    }

    void Controls::DrawLoadButton() {
        SDL_Rect _block_load;
        _block_load.x = RIGHT_MID - (tileSize_*1.5);
        _block_load.y = GAP + ((GAP + tileSize_) * 2);
        _block_load.w = tileSize_ * 3;
        _block_load.h = tileSize_;
        if (!loadButtonPressed_) {
            SDL_SetRenderDrawColor(m_Renderer, 0, 200, 200, 200);
        } else {
            SDL_SetRenderDrawColor(m_Renderer, 0, 115, 115, 115);
        }
        SDL_RenderFillRect(m_Renderer, &_block_load);

        SDL_SetRenderDrawColor(m_Renderer, 0,0,0,0);
        SDL_RenderDrawRect(m_Renderer, &_block_load);
    }

    void Controls::DrawSolveButton() {
        SDL_Rect _block_solve;
        _block_solve.x = RIGHT_MID - (tileSize_*1.5);
        _block_solve.y = GAP + ((GAP + tileSize_) * 3);
        _block_solve.w = tileSize_ * 3;
        _block_solve.h = tileSize_;
        if (!solveButtonPressed_) {
            SDL_SetRenderDrawColor(m_Renderer, 0, 200, 200, 200);
        } else {
            SDL_SetRenderDrawColor(m_Renderer, 0, 115, 115, 115);
        }
        SDL_RenderFillRect(m_Renderer, &_block_solve);

        SDL_SetRenderDrawColor(m_Renderer, 0,0,0,0);
        SDL_RenderDrawRect(m_Renderer, &_block_solve);
    }
    
    void Controls::DrawControls() {
        upArrowLvl_->Draw();
        downArrowLvl_->Draw();
        upArrowStage_->Draw();
        downArrowStage_->Draw();
    }

    void Controls::Render() {
        DrawLoadButton();
        DrawSolveButton();
        DrawText();
        DrawControls();

    }
    
    void Controls::Free() {
        SDL_FreeSurface(levelTextSurface_);
        SDL_DestroyTexture(levelTextTexture_);
        SDL_FreeSurface(stageTextSurface_);
        SDL_DestroyTexture(stageTextTexture_);
    }

    bool Controls::GetChangeLvl() { return loadButtonPressed_; }

    bool Controls::GetStartSolver() {
        if (solveButtonPressed_){
            solveButtonPressed_ = false;
            return true;
        } else {
            return false;
        }
    }

    int Controls::CheckNumBounds(int value, int change){
        int out = value + change;
        if (out > 9){ return 1; }
        if (out < 1){ return 9; }
        return out;
    }

    std::string Controls::GetLvlFilename(){
        std::string stage_name = std::to_string(stage_);
        std::string level_name = std::to_string(level_);
        std::string filename = ("../levels/stage_" + stage_name + "/" + 
            stage_name + "_level_" + level_name + ".csv");
        loadButtonPressed_ = false;
        return filename;
    }
}


