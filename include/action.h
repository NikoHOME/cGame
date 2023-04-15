#pragma once

struct Action
{
    int previousPositionX, previousPositionY;
    int newPositionX, newPositionY;
    int organismIndex;
};

struct collisionAction
{
    int realStrength;
    int temporaryStrength;
    bool canKill;
    bool moved;
    bool stopAfterThis;
    bool canDieAfterFail = true;
};