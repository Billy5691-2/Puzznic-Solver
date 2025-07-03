#include "../../include/GUI/itemCounter.hpp"

namespace GUI {
    ItemCounter::ItemCounter(SDL_Renderer* p_Renderer, int p_tile_size, std::array<const char*, COLOURS> item_paths) {
        TTF_Init();
        m_Renderer = p_Renderer;
        tile_size = p_tile_size;

        Sans = TTF_OpenFont("../assets/fonts/OpenSans-Regular.ttf", 30);
        //Sans = TTF_OpenFont("Sans.ttf", 24);

        if (Sans == NULL) { 
            std::cout << "Opening font failed!\n";
        }

        White = {255, 255, 255};

        for (int i = 0; i < COLOURS; i++) {
            Tiles* temp = new Tiles(m_Renderer, item_paths[i], tile_size);
            temp->setPosition((WINDOW_LEFT / 4), tile_size + (i * (tile_size + 10)));
            item_count_tiles[i] = temp;
        }
    }

    ItemCounter::~ItemCounter(){
        TTF_CloseFont(Sans);
        TTF_Quit();
    }

    void ItemCounter::draw_tiles(){
        for (int i=0; i < COLOURS; i++) {
            item_count_tiles[i]->draw();
        }
    }

    void ItemCounter::draw_text(std::array<int, COLOURS> item_count){
        for (int i = 0; i < COLOURS; i++) {

            std::string temp_str = std::to_string(item_count[i]);
            temp_str = "x" + temp_str;
            char const *pchar = temp_str.c_str();
            

            SDL_Surface* surface_message = TTF_RenderText_Solid(Sans, pchar, White);
            SDL_Texture* message = SDL_CreateTextureFromSurface(m_Renderer, surface_message);
            SDL_Rect message_rect;

            int w, h;
            TTF_SizeText(Sans, pchar, &w, &h);

            message_rect.x = (WINDOW_LEFT / 4) + tile_size + 5;
            message_rect.y = tile_size + (i * (tile_size + 10)) - 3;
            message_rect.w = w;
            message_rect.h = h;
            SDL_RenderCopy(m_Renderer, message, NULL, &message_rect);

            surfaces[i] = surface_message;
            messages[i] = message;

        }
    }

    void ItemCounter::free_text(){
        for (int i =0; i < COLOURS; i++) {
            SDL_FreeSurface(surfaces[i]);
            SDL_DestroyTexture(messages[i]);
        }
    }
}