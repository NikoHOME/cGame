#include "plant.h"
#include <iostream>
#include "world.h"

class Grass : public Plant
{   
    public:
        Grass(int x, int y) : Plant(0,0,x,y) {}
        const char *getChar() const 
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(GRASS_COLOUR)); 
            return "G";
        }
        const char *getName() const {return "Grass";}
        Grass *reproduce(int x, int y) 
        {
            return new Grass(x,y);
        }
};
class Dandelion : public Plant
{   
    public:
        Dandelion(int x, int y) : Plant(0,0,x,y) {}
        const char *getChar() const 
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(DANDELION_COLOUR)); 
            return "D";
        }
        const char *getName() const {return "Dandelion";}
        void action();
        Dandelion *reproduce(int x, int y) 
        {
            return new Dandelion(x,y);
        }
};

class Guarana : public Plant
{   
    public:
        Guarana(int x, int y) : Plant(0,0,x,y) {}
        const char *getChar() const 
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(GUARANA_COLOUR)); 
            return "G";
        }
        const char *getName() const {return "Guarana";}
        CollisionAction collision();
        Guarana *reproduce(int x, int y) 
        {
            return new Guarana(x,y);
        }
};

class Belladonna : public Plant
{   
    public:
        Belladonna(int x, int y) : Plant(99,0,x,y) {}
        const char *getChar() const 
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(BELLADONA_COLOUR)); 
            return "B";
        }
        const char *getName() const {return "Belladonna";}
        CollisionAction collision();
        Belladonna *reproduce(int x, int y) 
        {
            return new Belladonna(x,y);
        }
};

class SosnowskyHogweed : public Plant
{   
    public:
        SosnowskyHogweed(int x, int y) : Plant(10,0,x,y) {}
        const char *getChar() const 
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(HOGWEED_COLOUR)); 
            return "H";
        }
        const char *getName() const {return "Sosnowsky hogweed";}
        void action();
        CollisionAction collision();
        SosnowskyHogweed *reproduce(int x, int y) 
        {
            return new SosnowskyHogweed(x,y);
        }
};


