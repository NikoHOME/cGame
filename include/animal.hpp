#pragma once
#include "organism.hpp"
#include "action.hpp"

class Animal : public Organism
{
    using Organism::Organism;
    protected:
        MovementAction movementAction;
    public:
        virtual void action();
        virtual CollisionAction collision();
        virtual const char *getName() const { return "Animal";}
        virtual const char *getChar() const { return "?";}
        virtual const char *getKillMessage() const override {return "eaten";}
        virtual const char *getBornMessage() const override {return "was born";}
        virtual void write(std::ofstream &file) = 0;
        void basicMovementHandle();
        void basicCollisionHandle();
        virtual bool isSameSpecies(Organism *animal) = 0;
        
        bool reproduceCollision(Organism *otherOrganism);

};


