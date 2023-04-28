#include "world.hpp"
#include "plant.hpp"

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
        void write(std::ofstream &file)
        {
            file << DANDELION_ID << "\n";
            writeBasic(file);
        }
};