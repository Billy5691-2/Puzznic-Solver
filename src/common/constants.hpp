#ifndef AF5BCDEA_F606_43F0_BDE8_6825F7D9F73A
#define AF5BCDEA_F606_43F0_BDE8_6825F7D9F73A

constexpr int BOARD_SIZE = 20;

constexpr int WINDOW_HEIGHT = 900;
constexpr int WINDOW_WIDTH = WINDOW_HEIGHT * 1.6;
constexpr int WINDOW_LEFT = (WINDOW_WIDTH - WINDOW_HEIGHT) * 0.4;       // Righthand edge of window leftside
constexpr int WINDOW_RIGHT_OFFSET = WINDOW_HEIGHT + WINDOW_LEFT;        // Lefthand side of window rightside
constexpr int WINDOW_RIGHT_SIZE = (WINDOW_WIDTH - WINDOW_HEIGHT) * 0.6; // Lefthand side of window rightside

constexpr int RIGHT_MID = WINDOW_RIGHT_OFFSET + (WINDOW_RIGHT_SIZE / 2);

constexpr int TILE_SIZE = WINDOW_HEIGHT / BOARD_SIZE;

constexpr int MAX_LEVEL_VALUE = 9;
constexpr int MIN_LEVEL_VALUE = 1;

constexpr unsigned int NO_ITEM_SELECTED = 8192;

// const int WINDOW_WIDTH = 1200;
#endif /* AF5BCDEA_F606_43F0_BDE8_6825F7D9F73A */
