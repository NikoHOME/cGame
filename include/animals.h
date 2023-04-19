#include "animal.h"
#include <iostream>

class Wolf : public Animal
{   
    public:
        Wolf(int x, int y) : Animal(9,5,x,y) {}
        void draw() const {std::cout<<"W ";}
        void printName() const { std::cout<<"Wolf";}
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
        void draw() const {std::cout<<"S ";}
        void printName() const { std::cout<<"Sheep";}
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
        void draw() const {std::cout<<"F ";}
        void printName() const { std::cout<<"Fox";}
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
        void draw() const {std::cout<<"T ";}
        void printName() const { std::cout<<"Turtle";}
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
        void draw() const {std::cout<<"A ";}
        void printName() const { std::cout<<"Antilope";}
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

