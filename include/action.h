#pragma once

struct Action
{
    int previousPositionX, previousPositionY;
    int newPositionX, newPositionY;
    int organismIndex;
};

struct MovementAction
{
    std:: pair <int,int> direction;
    int newPositionX, newPositionY;
};

struct CollisionAction
{
    int realStrength;
    int tempAttackStrength = -1;
    int tempDefenceStrength = -1;
    bool hasTempAttackStrength = false;
    bool hasTempDefenceStrength = false;
    int givenStrength = -1;
    bool givesStrength = false;
    bool escaped = false;
    bool killAfterDefeat = false;

};

struct AttackAction
{
    int thisAttackerStrength;
    int thisDefenderStrength;
    int otherAttackerStrength;
    int otherDefenderStrength;
};