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
        m_Font = p_Font;
        m_Txt_Colour = p_Txt_Colour;
        tile_size = p_tile_size;

        up_arrow_lvl = new Tiles(m_Renderer, UP_ARROW_PATH, tile_size);
        up_arrow_lvl->setPosition(RIGHT_MID - (tile_size*1.5), GAP);

        up_arrow_stage = new Tiles(m_Renderer, UP_ARROW_PATH, tile_size);
        up_arrow_stage->setPosition(RIGHT_MID - (tile_size*1.5), GAP + GAP + tile_size);

        down_arrow_lvl = new Tiles(m_Renderer, DOWN_ARROW_PATH, tile_size);
        down_arrow_lvl->setPosition(RIGHT_MID + (tile_size*0.5), GAP);

        down_arrow_stage = new Tiles(m_Renderer, DOWN_ARROW_PATH, tile_size);
        down_arrow_stage->setPosition(RIGHT_MID + (tile_size*0.5), GAP + GAP + tile_size);
        
        int w, h;
        load_surface = TTF_RenderText_Solid(m_Font, "Load", m_Txt_Colour);
        load_texture = SDL_CreateTextureFromSurface(m_Renderer, load_surface);
        TTF_SizeText(m_Font, "Load", &w, &h);

        load_rect.x = RIGHT_MID - (w / 2);
        load_rect.y = GAP + ((GAP + tile_size) * 2);
        load_rect.w = w;
        load_rect.h = h;

        solve_surface = TTF_RenderText_Solid(m_Font, "Solve", m_Txt_Colour);
        solve_texture = SDL_CreateTextureFromSurface(m_Renderer, solve_surface);
        TTF_SizeText(m_Font, "Solve", &w, &h);

        solve_rect.x = RIGHT_MID - (w / 2);
        solve_rect.y = GAP + ((GAP + tile_size) * 3);
        solve_rect.w = w;
        solve_rect.h = h;

    }

    Controls::~Controls(){
        SDL_FreeSurface(load_surface);
        SDL_DestroyTexture(load_texture);
        SDL_FreeSurface(solve_surface);
        SDL_DestroyTexture(solve_texture);
        std::cout << "Controls destroyed\n";
    }

    void Controls::handle_click(int x, int y){
        if (y > GAP && y < GAP + tile_size) {
            if (x > RIGHT_MID - (tile_size*1.5) && x < RIGHT_MID - (tile_size*0.5)) {
                //Up arrow level
                level = bound_check(level, 1);
            } else if (x > RIGHT_MID + (tile_size*0.5) && x < RIGHT_MID + (tile_size*1.5)){
                //Down arrow level
                level = bound_check(level, -1);
            }
        } else if (y > GAP + (GAP + tile_size) && y < GAP + tile_size + (GAP + tile_size)) {
            if (x > RIGHT_MID - (tile_size*1.5) && x < RIGHT_MID - (tile_size*0.5)) {
                //Up arrow stage
                stage = bound_check(stage, 1);
            } else if (x > RIGHT_MID + (tile_size*0.5) && x < RIGHT_MID + (tile_size*1.5)){
                //Down arrow stage
                stage = bound_check(stage, -1);
            }
        } else if (y > GAP + ((GAP + tile_size) * 2) && 
        y < GAP + tile_size + ((GAP + tile_size) * 2)) {
            if (x > RIGHT_MID - (tile_size*1.5) && x < RIGHT_MID + (tile_size*1.5)) {
                load_pressed = true;
                //load button
            }
        } else if (y > GAP + ((GAP + tile_size) * 3) && 
        y < GAP + tile_size + ((GAP + tile_size) * 3)) {
            if (x > RIGHT_MID - (tile_size*1.5) && x < RIGHT_MID + (tile_size*1.5)) {
                solve_pressed = true;
                //solve button
            }
        }
    }

    void Controls::draw_text() {
        SDL_RenderCopy(m_Renderer, load_texture, NULL, &load_rect);
        SDL_RenderCopy(m_Renderer, solve_texture, NULL, &solve_rect);

        std::string temp_str = std::to_string(level);
        char const *level_char = temp_str.c_str();

        int w, h;
        level_surface = TTF_RenderText_Solid(m_Font, level_char, m_Txt_Colour);
        level_texture = SDL_CreateTextureFromSurface(m_Renderer, level_surface);
        TTF_SizeText(m_Font, level_char, &w, &h);

        SDL_Rect level_rect;
        level_rect.x = RIGHT_MID - (w / 2);
        level_rect.y = GAP;
        level_rect.w = w;
        level_rect.h = h;

        SDL_RenderCopy(m_Renderer, level_texture, NULL, &level_rect);
        
        temp_str = std::to_string(stage);
        char const *stage_char = temp_str.c_str();

        stage_surface = TTF_RenderText_Solid(m_Font, stage_char, m_Txt_Colour);
        stage_texture = SDL_CreateTextureFromSurface(m_Renderer, stage_surface);
        TTF_SizeText(m_Font, stage_char, &w, &h);

        SDL_Rect stage_rect;
        stage_rect.x = RIGHT_MID - (w / 2);
        stage_rect.y = GAP + (tile_size + GAP);
        stage_rect.w = w;
        stage_rect.h = h;

        SDL_RenderCopy(m_Renderer, stage_texture, NULL, &stage_rect);

    }

    void Controls::draw_load() {
        SDL_Rect _block_load;
        _block_load.x = RIGHT_MID - (tile_size*1.5);
        _block_load.y = GAP + ((GAP + tile_size) * 2);
        _block_load.w = tile_size * 3;
        _block_load.h = tile_size;
        if (!load_pressed) {
            SDL_SetRenderDrawColor(m_Renderer, 0, 200, 200, 200);
        } else {
            SDL_SetRenderDrawColor(m_Renderer, 0, 115, 115, 115);
        }
        SDL_RenderFillRect(m_Renderer, &_block_load);

        SDL_SetRenderDrawColor(m_Renderer, 0,0,0,0);
        SDL_RenderDrawRect(m_Renderer, &_block_load);
    }

    void Controls::draw_solve() {
        SDL_Rect _block_solve;
        _block_solve.x = RIGHT_MID - (tile_size*1.5);
        _block_solve.y = GAP + ((GAP + tile_size) * 3);
        _block_solve.w = tile_size * 3;
        _block_solve.h = tile_size;
        if (!solve_pressed) {
            SDL_SetRenderDrawColor(m_Renderer, 0, 200, 200, 200);
        } else {
            SDL_SetRenderDrawColor(m_Renderer, 0, 115, 115, 115);
        }
        SDL_RenderFillRect(m_Renderer, &_block_solve);

        SDL_SetRenderDrawColor(m_Renderer, 0,0,0,0);
        SDL_RenderDrawRect(m_Renderer, &_block_solve);
    }
    
    void Controls::draw_controls() {
        up_arrow_lvl->draw();
        down_arrow_lvl->draw();
        up_arrow_stage->draw();
        down_arrow_stage->draw();
    }

    void Controls::render() {
        draw_load();
        draw_solve();
        draw_text();
        draw_controls();

    }
    
    void Controls::free() {
        SDL_FreeSurface(level_surface);
        SDL_DestroyTexture(level_texture);
        SDL_FreeSurface(stage_surface);
        SDL_DestroyTexture(stage_texture);
    }

    bool Controls::change_level() { return load_pressed; }

    bool Controls::start_solver() {
        if (solve_pressed){
            solve_pressed = false;
            return true;
        } else {
            return false;
        }
    }

    int Controls::bound_check(int value, int change){
        int out = value + change;
        if (out > 9){ return 1; }
        if (out < 1){ return 9; }
        return out;
    }

    std::string Controls::new_level_file(){
        std::string stage_name = std::to_string(stage);
        std::string level_name = std::to_string(level);
        std::string filename = ("../levels/stage_" + stage_name + "/" + 
            stage_name + "_level_" + level_name + ".csv");
        load_pressed = false;
        return filename;
        //const char *output = filename.c_str();
        //return output;
    }
}


