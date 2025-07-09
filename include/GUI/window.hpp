#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <map>

#include "tiles.hpp"
#include "board_background.hpp"
#include "item_counter.hpp"
#include "controls.hpp"
//#include <stdlib.h>
#include "../structs.hpp"
#include "../constants.hpp"
#include "../texture_paths.hpp"


// Platform output is untested

namespace GUI {
    class Window {
        SDL_Event* m_Event;
        SDL_Renderer* m_Renderer;
        SDL_Window* m_Window;

        int tileSize_;

        bool m_Running = false;

        bool levelChange_ = false;
        bool solveChange_ = false;
        bool moveChange_ = false;

        ItemCounter* m_Count;
        BoardBackground* m_Board;
        Controls* m_Controls;

        std::vector<Tiles*> baseTilesVec_;
        std::vector<Tiles*> platformTilesVec_;
        std::vector<Tiles*> itemTiles_;
        std::vector<Tiles*> itemCountTiles_;
        std::vector<Tiles*> moveTiles_;

        bool highlightChange_;
        move movePair_;

        TTF_Font* m_Font_;
        SDL_Colour m_TextColour_;

        void init();
        void DrawBoard();
        void ResetBoard(board board_data);
        void ResetPlatform(std::vector<platform> platform_list);
        void ResetItems(std::map<position, int> item_list);

        void ResetMoves(std::vector<position> move_list);

        void DeletePlatforms();
        void DeleteBoard();
        void DeleteItems();

        void DeleteMoves();

        void RenderBoard();
        void RenderPlatforms(std::vector<platform> platform_list);
        void RenderItems(std::map<position, int> item_list);
        
        void RenderMoves(std::vector<position> move_list);

        position GridToPixel(position pos);
        position GridToPixel(int x, int y);

        void DrawHighlight();

        public:
            Window(const char* title, board board_data, std::vector<platform> platform_list);
            ~Window();

            bool IsRunning() const;
            void PollEvent();
            bool Update();
            void Render(std::map<position, int> item_list, std::vector<platform> platform_list, 
                std::array<int, COLOURS> item_count, std::vector<position> move_list);

            void Reset(board board_data, std::vector<platform> platform_list);
            
            std::string GetLvlFilename();
            move GetMove();

            bool ChangeLevelState();
            bool StartSolverState();
            bool GetHightlightChange();

                
        };
}