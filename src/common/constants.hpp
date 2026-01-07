#ifndef AF5BCDEA_F606_43F0_BDE8_6825F7D9F73A
#define AF5BCDEA_F606_43F0_BDE8_6825F7D9F73A

const int BOARD_SIZE = 20;

const int WINDOW_HEIGHT = 900;
const int WINDOW_WIDTH = WINDOW_HEIGHT * 1.6;
const int WINDOW_LEFT = (WINDOW_WIDTH - WINDOW_HEIGHT) * 0.4;        // Righthand edge of window leftside
const int WINDOW_RIGHT_OFFSET = WINDOW_HEIGHT + WINDOW_LEFT;         // Lefthand side of window rightside
const int WINDOW_RIGHT_SIZE = (WINDOW_WIDTH - WINDOW_HEIGHT) * 0.6;  // Lefthand side of window rightside

const int RIGHT_MID = WINDOW_RIGHT_OFFSET + (WINDOW_RIGHT_SIZE / 2);

const int TILE_SIZE = WINDOW_HEIGHT / BOARD_SIZE;

// const int WINDOW_WIDTH = 1200;
#endif /* AF5BCDEA_F606_43F0_BDE8_6825F7D9F73A */
