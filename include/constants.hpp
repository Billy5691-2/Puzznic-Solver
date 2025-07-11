#pragma once

const int kBoardSize = 20;

const int COLOURS = 9;

const int WINDOW_HEIGHT = 900;
const int WINDOW_WIDTH = WINDOW_HEIGHT * 1.6;
const int WINDOW_LEFT = (WINDOW_WIDTH - WINDOW_HEIGHT) * 0.4; // Righthand edge of window leftside
const int WINDOW_RIGHT_OFFSET = WINDOW_HEIGHT + WINDOW_LEFT; //Lefthand side of window rightside
const int WINDOW_RIGHT_SIZE = (WINDOW_WIDTH - WINDOW_HEIGHT) * 0.6; //Lefthand side of window rightside

const int RIGHT_MID = WINDOW_RIGHT_OFFSET + (WINDOW_RIGHT_SIZE / 2);

//const int WINDOW_WIDTH = 1200;
