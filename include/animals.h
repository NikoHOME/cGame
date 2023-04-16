#include "animal.h"
#include <iostream>

class Wolf : public Animal
{   
    public:
        Wolf(int x, int y) : Animal(9,5,x,y,"Wolf") {}
        void draw() const {std::cout<<"W ";}
        void printName() const { std::cout<<"Wolf";}
        Wolf *reproduce(Organism *animal, int x,int y) 
        { 
            auto mate = dynamic_cast<Wolf *>(animal);
            if (!mate) return nullptr;
            return new Wolf(x,y);
        }
};

class Sheep : public Animal
{  
    public:
        Sheep(int x, int y) : Animal(4,4,x,y,"Sheep") {}
        void draw() const {std::cout<<"S ";}
        void printName() const { std::cout<<"Sheep";}
        Sheep *reproduce(Organism *animal, int x,int y) 
        { 
            auto mate = dynamic_cast<Sheep *>(animal);
            if (!mate) return nullptr;
            return new Sheep(x,y);
        }
};

class Fox : public Animal
{  

    public:
        Fox(int x, int y) : Animal(3,7,x,y,"Fox") {}
        void draw() const {std::cout<<"F ";}
        void printName() const { std::cout<<"Fox";}
        void action();
        Fox *reproduce(Organism *animal, int x,int y) 
        { 
            auto mate = dynamic_cast<Fox *>(animal);
            if (!mate) return nullptr;
            return new Fox(x,y);
        }
};

class Turtle : public Animal
{  
    public:
        Turtle(int x, int y) : Animal(2,1,x,y,"Turtle") {}
        void draw() const {std::cout<<"T ";}
        void printName() const { std::cout<<"Turtle";}
        void action();
        CollisionAction collision();
        Turtle *reproduce(Organism *animal, int x,int y) 
        { 
            auto mate = dynamic_cast<Turtle *>(animal);
            if (!mate) return nullptr;
            return new Turtle(x,y);
        }
};

class Antilope : public Animal
{  
    public:
        Antilope(int x, int y) : Animal(4,4,x,y,"Antilope") {}
        void draw() const {std::cout<<"A ";}
        void printName() const { std::cout<<"Antilope";}
        void action();
        CollisionAction collision();
        Antilope *reproduce(Organism *animal, int x,int y) 
        { 
            auto mate = dynamic_cast<Antilope *>(animal);
            if (!mate) return nullptr;
            return new Antilope(x,y);
        }
};

