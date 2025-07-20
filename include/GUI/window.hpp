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
        Move movePair_;

        TTF_Font* m_Font_;
        SDL_Colour m_TextColour_;

        void init();
        void DrawBoard();
        void ResetBoard(const BoardArr& board_data);
        void ResetPlatform(const std::vector<Platform>& platform_list);
        void ResetItems(const std::map<Coord, int>& item_list);

        void ResetMoves(const std::vector<Coord>& move_list);

        void DeletePlatforms();
        void DeleteBoard();
        void DeleteItems();

        void DeleteMoves();

        void RenderBoard();
        void RenderPlatforms(const std::vector<Platform>& platform_list);
        void RenderItems(const std::map<Coord, int>& item_list);
        
        void RenderMoves(const std::vector<Coord>& move_list);

        Coord GridToPixel(Coord pos);
        Coord GridToPixel(int x, int y);

        void DrawHighlight();

        public:
            Window(const char* title, const BoardArr& board_data, 
                const std::vector<Platform>& platform_list, int boardSize);
            ~Window();

            bool IsRunning() const;
            void PollEvent();
            bool Update();
            void Render(const std::map<Coord, int>& item_list, const std::vector<Platform>& platform_list, 
                const std::array<int, COLOURS>& item_count, const std::vector<Coord>& move_list);

            void Reset(const BoardArr& board_data, const std::vector<Platform>& platform_list);
            
            std::string GetLvlFilename();
            Move GetMove();

            bool ChangeLevelState();
            bool StartSolverState();
            bool GetHightlightChange();

                
        };
}