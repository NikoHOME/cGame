#pragma once

#include <iostream>
#include "classes.h"
#include "action.h"
#include <string.h>

class Organism
{
    protected:
        int strength;
        int innitiative;
        int positionX,positionY;
        int index;
        bool isDead;
        World *world;
        std::string species;
    public:
        int getStrength() const;
        int getInnitiative() const;
        int getPositionX() const;
        int getPositionY() const;
        int getIndex() const;
        std::string getName() const;
        bool getIsDeadStatus() const;
        World *getWorld() const;

        void setStrength(int str);
        void setInnitiative(int ini);
        void setPositionX(int x);
        void setPositionY(int y);
        void setIndex(int ind);
        void setIsDeadStatus(bool dead);
        void setWorld(World *world); 

        Organism()
        {
            world = nullptr;
        }
        Organism(int str, int init, int x, int y, std::string name = " ") : 
        strength(str), innitiative(init), positionX(x), positionY(y), species(name)  
        {
            world = nullptr;
        };
        Organism(const Organism &organism);

        virtual void action() = 0;
        virtual CollisionAction collision() = 0;
        virtual void draw() const = 0;
        virtual void printName() const = 0;

};