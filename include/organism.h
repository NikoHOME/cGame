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
        bool isDead = false;
        World *world;
    public:
        int getStrength() const;
        int getInnitiative() const;
        int getPositionX() const;
        int getPositionY() const;
        int getIndex() const;
        bool getIsDeadStatus() const;
        World *getWorld() const;
        int getAge() const;

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
        Organism(int str, int init, int x, int y) : 
        strength(str), innitiative(init), positionX(x), positionY(y)
        {
            world = nullptr;
        };
        Organism(const Organism &organism);

        virtual Organism *reproduce(int x, int y) = 0; 
        void die();

        virtual void action() = 0;
        virtual CollisionAction collision() = 0;
        virtual const char *getName() const = 0;
        virtual const char *getChar() const = 0;

};