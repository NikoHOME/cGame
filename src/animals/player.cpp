#include "animals/player.hpp"

#define INFINITY INT32_MAX

bool Player::inputAction()
{
    Coordinate coordinate;
    coordinate.x = positionX;
    coordinate.y = positionY;
    World *world = getWorld();
    switch(world->getPlayerAction())
    {
        case MOVE_UP:
            coordinate.y--;
            break;
        case MOVE_DOWN:
            coordinate.y++;
            break;
        case MOVE_LEFT:
            coordinate.x--;
            break;
        case MOVE_RIGHT:
            coordinate.x++;
            break;
    }

    if(!isInBounds(world->getBoardSize(), coordinate))
        return false;
    movementAction.newPositionX = coordinate.x;
    movementAction.newPositionY = coordinate.y;
    world->getQueue().push(world->getOrganismDisplay()[positionX][positionY]);
    return true;

}

void Player::action()
{
    basicCollisionHandle();
    getWorld()->setPlayerPosX(positionX);
    getWorld()->setPlayerPosY(positionY);
}

CollisionAction Player::collision()
{
    CollisionAction action;
    action.realStrength = strength;
    if(world->playerHasAbility())
    {
        action.hasTempDefenceStrength = true;
        action.tempDefenceStrength = INFINITY; 
        action.escapeAfterFailedAttack = true;
        action.isImmortal = true;
    }
    return action;
}
