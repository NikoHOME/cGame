#include "plant.h"
#include <iostream>

class Grass : public Plant
{   
    public:
        Grass(int x, int y) : Plant(0,0,x,y) {}
        void draw() const {std::cout<<"G ";}
        void printName() const { std::cout<<"Grass";}
        Grass *reproduce(int x, int y) 
        {
            return new Grass(x,y);
        }
};
class Dandelion : public Plant
{   
    public:
        Dandelion(int x, int y) : Plant(0,0,x,y) {}
        void draw() const {std::cout<<"D ";}
        void printName() const { std::cout<<"Dandelion";}
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
        void draw() const {std::cout<<"D ";}
        void printName() const { std::cout<<"Guarana";}
        CollisionAction collision();
        Guarana *reproduce(int x, int y) 
        {
            return new Guarana(x,y);
        }
};

class WolfBerry : public Plant
{   
    public:
        WolfBerry(int x, int y) : Plant(99,0,x,y) {}
        void draw() const {std::cout<<"B ";}
        void printName() const { std::cout<<"Wolfberry";}
        CollisionAction collision();
        WolfBerry *reproduce(int x, int y) 
        {
            return new WolfBerry(x,y);
        }
};

class SosnowskyHogweed : public Plant
{   
    public:
        SosnowskyHogweed(int x, int y) : Plant(10,0,x,y) {}
        void draw() const {std::cout<<"H ";}
        void printName() const { std::cout<<"Sosnowsky hogweed";}
        void action();
        CollisionAction collision();
        SosnowskyHogweed *reproduce(int x, int y) 
        {
            return new SosnowskyHogweed(x,y);
        }
};


