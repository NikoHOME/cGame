#pragma once
#include "classes.hpp"
#include <ncurses.h>

struct Coordinate
{
    int x, y;
};

struct BoardSize
{
    int width, height;
};

struct WorldData
{
    BoardSize boardSize;
    int turn = 0;
    int newAnimalIndex = 0;
    int playerPosX, playerPosY;
    char playerInput;
    bool playerAlive = true;
    int lastTimeAbilityUsed = -10;
    int AbilityDuration = 0;
};

#define MAX_BOARD_SIZE_Y (LINES/2-1) //Max window size based on terminal
#define MAX_BOARD_SIZE_X (COLS/4)


bool isInBounds(BoardSize boardSize, Coordinate coordinate);
