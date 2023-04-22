#include "animal.h"
#include <iostream>
#include "world.h"


class Player : public Animal
{
    public:
        Player(int x,int y) : Animal(5,4,x,y) {}
        const char *getChar() const 
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(PLAYER_COLOUR)); 
            return "@";
        }
        const char *getName() const {return "Player";}
        void inputAction();
        void action();
        //CollisionAction collision() {return collision;}
        bool isSameSpecies(Organism *animal) { return false;}
        Player *reproduce(int x,int y) { return this;}      
};

class Wolf : public Animal
{   
    public:
        Wolf(int x, int y) : Animal(9,5,x,y) {}
        const char *getChar() const 
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(WOLF_COLOUR)); 
            return "W";
        }
        const char *getName() const {return "Wolf";}
        bool isSameSpecies(Organism *animal)
        {
            auto mate = dynamic_cast<Wolf *>(animal);
            if (!mate) return false;
            return true;
        }
        Wolf *reproduce(int x,int y) 
        {
            return new Wolf(x,y);
        }
};

class Sheep : public Animal
{  
    public:
        Sheep(int x, int y) : Animal(4,4,x,y) {}
        const char *getChar() const 
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(SHEEP_COLOUR)); 
            return "S";
        }
        const char *getName() const {return "Sheep";}
        bool isSameSpecies(Organism *animal)
        {
            auto mate = dynamic_cast<Sheep *>(animal);
            if (!mate) return false;
            return true;
        }
        Sheep *reproduce(int x,int y) 
        {
            return new Sheep(x,y);
        }
};

class Fox : public Animal
{  

    public:
        Fox(int x, int y) : Animal(3,7,x,y) {}
        const char *getChar() const 
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(FOX_COLOUR)); 
            return "F";
        }
        const char *getName() const {return "Fox";}
        void action();
        bool isSameSpecies(Organism *animal)
        {
            auto mate = dynamic_cast<Fox *>(animal);
            if (!mate) return false;
            return true;
        }
        Fox *reproduce(int x,int y) 
        { 
            return new Fox(x,y);
        }
};

class Turtle : public Animal
{  
    public:
        Turtle(int x, int y) : Animal(2,1,x,y) {}
        const char *getChar() const 
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(TURTLE_COLOUR)); 
            return "T";
        }
        const char *getName() const {return "Turtle";}
        void action();
        CollisionAction collision();
        bool isSameSpecies(Organism *animal)
        {
            auto mate = dynamic_cast<Turtle *>(animal);
            if (!mate) return false;
            return true;
        }
        Turtle *reproduce(int x,int y) 
        {
            return new Turtle(x,y);
        }
};

class Antilope : public Animal
{  

    public:
        Antilope(int x, int y) : Animal(4,4,x,y) {}
        const char *getChar() const 
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(ANTILOPE_COLOUR)); 
            return "A";
        }
        const char *getName() const {return "Antilope";}
        void action();
        CollisionAction collision();
        bool isSameSpecies(Organism *animal)
        {
            auto mate = dynamic_cast<Antilope *>(animal);
            if (!mate) return false;
            return true;
        }
        Antilope *reproduce(int x,int y) 
        {
            return new Antilope(x,y);
        }
};

