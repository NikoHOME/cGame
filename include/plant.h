#include "organism.h"

class Plant : public Organism
{
    using Organism::Organism;

    void action(){};
    void collision(){};
    void draw() const;
};