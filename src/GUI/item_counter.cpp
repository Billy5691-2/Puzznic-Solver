#include "../../include/GUI/item_counter.hpp"

namespace GUI {
    ItemCounter::ItemCounter(SDL_Renderer* p_Renderer, TTF_Font* p_font, SDL_Colour p_txt_colour,
        int p_tile_size, std::array<const char*, COLOURS> item_paths) {
        m_Renderer = p_Renderer;
        tileSize_ = p_tile_size;
        
        m_Font_ = p_font;
        m_TextColour = p_txt_colour;

        for (int i = 0; i < COLOURS; i++) {
            Tiles* temp = new Tiles(m_Renderer, item_paths[i], tileSize_);
            temp->SetPosition((WINDOW_LEFT / 4), tileSize_ + (i * (tileSize_ + 10)));
            itemCountTilesArr_[i] = temp;
        }
    }

    ItemCounter::~ItemCounter(){
        std::cout << "Item Counter Closed\n";
    }

    void ItemCounter::DrawTiles(){
        for (int i=0; i < COLOURS; i++) {
            itemCountTilesArr_[i]->Draw();
        }
    }

    void ItemCounter::DrawText(std::array<int, COLOURS> item_count){
        for (int i = 0; i < COLOURS; i++) {

            std::string temp_str = std::to_string(item_count[i]);
            temp_str = "x" + temp_str;
            char const *pchar = temp_str.c_str();
            

            SDL_Surface* surface_message = TTF_RenderText_Solid(m_Font_, pchar, m_TextColour);
            SDL_Texture* message = SDL_CreateTextureFromSurface(m_Renderer, surface_message);
            SDL_Rect message_rect;

            int w, h;
            TTF_SizeText(m_Font_, pchar, &w, &h);

            message_rect.x = (WINDOW_LEFT / 4) + tileSize_ + 5;
            message_rect.y = tileSize_ + (i * (tileSize_ + 10)) - 3;
            message_rect.w = w;
            message_rect.h = h;
            SDL_RenderCopy(m_Renderer, message, NULL, &message_rect);

            surfacesArr_[i] = surface_message;
            texturesArr_[i] = message;

        }
    }

    void ItemCounter::Free(){
        for (int i =0; i < COLOURS; i++) {
            SDL_FreeSurface(surfacesArr_[i]);
            SDL_DestroyTexture(texturesArr_[i]);
        }
    }
}