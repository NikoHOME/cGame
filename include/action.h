#pragma once

struct Action
{
    int previousPositionX, previousPositionY;
    int newPositionX, newPositionY;
    int organismIndex;
};

struct CollisionAction
{
    int realStrength;
    int tempAttackStrength = -1;
    int tempDefenceStrength = -1;
    bool hasTempAttackStrength = false;
    bool hasTempDefenceStrength = false;
    bool escaped = false;
    bool stopAfterDefence = false;
    bool stopAfterAttack = false;
};

struct AttackAction
{
    int thisAttackerStrength;
    int thisDefenderStrength;
    int otherAttackerStrength;
    int otherDefenderStrength;
};