#include "world.hpp"
#include "plant.hpp"

class Guarana : public Plant
{   
    public:
        Guarana(int x, int y) : Plant(0,0,x,y) {}
        const char *getChar() const 
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(GUARANA_COLOUR)); 
            return "G";
        }
        const char *getName() const {return "Guarana";}
        CollisionAction collision();
        Guarana *reproduce(int x, int y) 
        {
            return new Guarana(x,y);
        }
        void write(std::ofstream &file)
        {
            file << GUARANA_ID << "\n";
            writeBasic(file);
        }
};