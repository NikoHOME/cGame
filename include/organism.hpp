#pragma once

#include <iostream>
#include "classes.hpp"
#include "action.hpp"
#include <string.h>
#include <fstream>

#define WOLF_ID 1
#define SHEEP_ID 2
#define TURTLE_ID 3
#define ANTILOPE_ID 4
#define FOX_ID 5
#define PLAYER_ID 6

#define GRASS_ID 7
#define DANDELION_ID 8
#define BELLADONA_ID 9
#define HOGWEED_ID 10
#define GUARANA_ID 11


#define INIFNITY INT32_MAX;

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

        void moveOrganism(int x, int y);
        void killIfStronger(Organism *inputOrganism, CollisionAction thisCollision, CollisionAction otherCollision);

        void writeBasic(std::ofstream &file);

        virtual void action() = 0;
        virtual CollisionAction collision() = 0;
        virtual const char *getName() const = 0;
        virtual const char *getChar() const = 0;
        virtual const char *getKillMessage() const {return "killed";}
        virtual const char *getBornMessage() const {return "was born";}
        virtual void write(std::ofstream &file) = 0;


};