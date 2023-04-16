#pragma once
#include "organism.h"

class Plant : public Organism
{
    using Organism::Organism;
    public:
        void action(){};
        CollisionAction collision();
        void draw() const;
        virtual void printName() const { std::cout<<"Plant";}
};