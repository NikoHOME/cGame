#include "organism.hpp"
#include "world.hpp"
#include "animal.hpp"
#include "plant.hpp"
#include <iostream>
#include <algorithm>

class World;

int Organism::getStrength() const
{
    return strength;
}
int Organism::getInnitiative() const
{
    return innitiative;
}
int Organism::getPositionX() const
{
    return positionX;
}
int Organism::getPositionY() const
{
    return positionY;
}
int Organism::getIndex() const
{
    return index;
}
bool Organism::getIsDeadStatus() const
{
    return isDead;
}
World *Organism::getWorld() const
{
    return world;
}
int Organism::getAge() const
{
    return world->getTurn() - index;
}


void Organism::setStrength(int str)
{
    strength = str;
}
void Organism::setInnitiative(int ini)
{
    innitiative = ini;
}
void Organism::setPositionX(int x)
{
    positionX = x;
}
void Organism::setPositionY(int y)
{
    positionY = y;
}
void Organism::setIndex(int ind)
{
    index = ind;
}
void Organism::setIsDeadStatus(bool dead)
{
    isDead = dead;
}
void Organism::setWorld(World *world)
{
    this->world = world;
}

        
Organism::Organism(const Organism &organism)
{
    this->strength = organism.getStrength();
    this->innitiative = organism.getInnitiative();
    this->positionX = organism.getPositionX();
    this->positionY = organism.getPositionY();
    this->world = organism.getWorld();
}

void Organism::die()
{
    isDead = true;

    Organism *organism = world->getOrganismDisplay()[positionX][positionY];
    world->getOrganismDisplay()[positionX][positionY] = nullptr;
    world->pushDeadOrganism(organism);
}


void Organism::moveOrganism(int x, int y)
{
    World *world = getWorld();
    Organism **organism = &world->getOrganismDisplay()[positionX][positionY]; 
    Organism **empty = &world->getOrganismDisplay()[x][y]; 

    setPositionX(x);
    setPositionY(y);

    //(*organism)->printName();
    //std::cout<<" : "<<(*organism)->getPositionX()<<" "<<(*organism)->getPositionY()<<" -> "<<x<<" "<<y<<"\n";

    std::swap(*empty, *organism); 
}

void setAction(AttackAction &action, CollisionAction thisCollision, CollisionAction otherCollision)
{
    if(thisCollision.hasTempAttackStrength)
        action.thisAttackerStrength = thisCollision.tempAttackStrength;
    else
        action.thisAttackerStrength = thisCollision.realStrength;
    
    if(thisCollision.hasTempDefenceStrength)
        action.thisDefenderStrength = thisCollision.tempDefenceStrength;
    else
        action.thisDefenderStrength = thisCollision.realStrength;


    if(otherCollision.hasTempAttackStrength)
        action.otherAttackerStrength = otherCollision.tempAttackStrength;
    else
        action.otherAttackerStrength = otherCollision.realStrength;
    
    if(otherCollision.hasTempDefenceStrength)
        action.otherDefenderStrength = otherCollision.tempDefenceStrength;
    else
        action.otherDefenderStrength = otherCollision.realStrength; 
}


void Organism::killIfStronger(Organism *inputOrganism, CollisionAction thisCollision, CollisionAction otherCollision)
{
    Organism **thisOrganism = &world->getOrganismDisplay()[positionX][positionY];
    Organism **otherOrganism = &world->getOrganismDisplay()[inputOrganism->getPositionX()][inputOrganism->getPositionY()];

    AttackAction action;

    setAction(action, thisCollision, otherCollision);

    if(action.thisAttackerStrength >= action.otherDefenderStrength)
    {

        if(otherCollision.givesStrength)
            (*thisOrganism)->setStrength((*thisOrganism)->getStrength() + otherCollision.givenStrength);

        if(otherCollision.killAfterDefeat && !thisCollision.isImmortal)
        {
            Message message1, message2;
            message1.animal1 = (*thisOrganism)->getName();
            message2.animal1 = (*otherOrganism)->getName();

            message1.animal2 = (*otherOrganism)->getName();
            message2.animal2 = (*thisOrganism)->getName();

            message1.message = (*thisOrganism)->getKillMessage();
            message2.message = (*otherOrganism)->getKillMessage();

            (*thisOrganism)->getWorld()->getManager()->pushMessage(message1);
            (*thisOrganism)->getWorld()->getManager()->pushMessage(message2);
            

            (*thisOrganism)->die();
            (*otherOrganism)->die();
            return;
        }

        //(*thisOrganism)->setPositionX((*otherOrganism)->getPositionX());
        //(*thisOrganism)->setPositionY((*otherOrganism)->getPositionY());

        Message message1;
        message1.animal1 = (*thisOrganism)->getName();
        message1.animal2 = (*otherOrganism)->getName();
        message1.message = (*thisOrganism)->getKillMessage();

        (*thisOrganism)->getWorld()->getManager()->pushMessage(message1);

        int newPosX = (*otherOrganism)->getPositionX();
        int newPosY = (*otherOrganism)->getPositionY();
        (*otherOrganism)->die();

        (*thisOrganism)->moveOrganism(newPosX, newPosY);
        //std::swap(*thisOrganism, *otherOrganism); 
    }

    if(thisCollision.escapeAfterFailedAttack && action.thisAttackerStrength < action.otherDefenderStrength)
    {   
        World *world = (*thisOrganism)->getWorld();
        int positionX = (*thisOrganism)->getPositionX();
        int positionY = (*thisOrganism)->getPositionY();
        
        std::vector< std::pair <int,int>> directions = world->getAiDirections();//[rand()%8];
        std::vector< std::pair <int,int>> safeDirections;


        Coordinate coordinate;
        for(int i=0 ;i < NORMAL_AI; ++i)
        {
            coordinate.x = positionX + directions[i].first;
            coordinate.y = positionY + directions[i].second;
            if(!isInBounds(world->getBoardSize(), coordinate))
                continue;
            auto target = world->getOrganismDisplay()[positionX + directions[i].first][positionY + directions[i].second];
            if(target == nullptr)
                safeDirections.push_back(directions[i]);
        }
        
        if(safeDirections.size() == 0)
            return;

        std::pair <int,int> direction = safeDirections[rand()%safeDirections.size()];

        (*thisOrganism)->moveOrganism(positionX + direction.first, positionY + direction.second);

        return;    
    }
    
    if(action.otherAttackerStrength > action.thisDefenderStrength)
    {
        if(thisCollision.givesStrength)
            (*otherOrganism)->setStrength((*otherOrganism)->getStrength() + thisCollision.givenStrength);

        Message message1;
        message1.animal1 = (*otherOrganism)->getName();
        message1.animal2 = (*thisOrganism)->getName();
        message1.message = (*otherOrganism)->getKillMessage();

        (*thisOrganism)->getWorld()->getManager()->pushMessage(message1);

       (*thisOrganism)->die();
    }
}


void Organism::writeBasic(std::ofstream &file)
{
    file << strength << " " << innitiative << " " << positionX << " " << positionY << " " << index << "\n";
}