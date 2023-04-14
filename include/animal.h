#include "organism.h"

class Animal : public Organism
{
    using Organism::Organism;

    void action();
    void collision(){};
    void draw() const;
};