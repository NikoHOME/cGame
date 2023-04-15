#include "animal.h"
#include <iostream>

class Wolf : public Animal
{   
    public:
        Wolf(int x, int y) : Animal(9,5,x,y) {}
        void draw() const {std::cout<<"W ";}
        void printName() const { std::cout<<"Wolf";}
};

class Sheep : public Animal
{  
    public:
        Sheep(int x, int y) : Animal(4,4,x,y) {}
        void draw() const {std::cout<<"S ";}
        void printName() const { std::cout<<"Sheep";}
};

class Fox : public Animal
{  

    public:
        Fox(int x, int y) : Animal(3,7,x,y) {}
        void draw() const {std::cout<<"F ";}
        void printName() const { std::cout<<"Fox";}
        void action();
};

class Turtle : public Animal
{  
    public:
        Turtle(int x, int y) : Animal(2,1,x,y) {}
        void draw() const {std::cout<<"T ";}
        void printName() const { std::cout<<"Turtle";}
        void action();
        collisionAction collision();
};

class Antilope : public Animal
{  
    public:
        Antilope(int x, int y) : Animal(4,4,x,y) {}
        void draw() const {std::cout<<"A ";}
        void printName() const { std::cout<<"Antilope";}
};

