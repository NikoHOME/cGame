#include "world.hpp"
#include "plant.hpp"

class Grass : public Plant
{   
    public:
        Grass(int x, int y) : Plant(0,0,x,y) {}
        const char *getChar() const 
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(GRASS_COLOUR)); 
            return "G";
        }
        const char *getName() const {return "Grass";}
        Grass *reproduce(int x, int y) 
        {
            return new Grass(x,y);
        }
        void write(std::ofstream &file)
        {
            file << GRASS_ID << "\n";
            writeBasic(file);
        }
};