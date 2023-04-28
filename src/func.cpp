#include "func.hpp"
#include <iostream>


bool isInBounds(BoardSize boardSize, Coordinate coordinate)
{
    if(coordinate.x >= 0 && coordinate.x < boardSize.width)
        if(coordinate.y >= 0 && coordinate.y < boardSize.height)
            return true;
    return false;
}

