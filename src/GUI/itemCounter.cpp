#include "../../include/GUI/itemCounter.hpp"

namespace GUI {
    ItemCounter::ItemCounter(SDL_Renderer* p_Renderer, int tile_size, std::array<const char*, COLOURS> item_paths) {
        TTF_Init();
        m_Renderer = p_Renderer;
        std::cout << "Opening font!\n";

        Sans = TTF_OpenFont("../../assets/fonts/OpenSans-Regular.ttf", 24);
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
            SDL_Surface* surface_message = TTF_RenderText_Solid(Sans, "Test", White);
            SDL_Texture* message = SDL_CreateTextureFromSurface(m_Renderer, surface_message);
            SDL_Rect message_rect;
            message_rect.x = WINDOW_LEFT / 2;
            message_rect.y = 100 * i;
            message_rect.w = 100;
            message_rect.h = 100;
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