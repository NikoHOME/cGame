#include "world.hpp"
#include "animal.hpp"

class Wolf : public Animal
{   
    public:
        Wolf(int x, int y) : Animal(9,5,x,y) {}
        const char *getChar() const 
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(WOLF_COLOUR)); 
            return "W";
        }
        const char *getName() const {return "Wolf";}
        virtual const char *getKillMessage() const {return "bit";}
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
        void write(std::ofstream &file)
        {
            file << WOLF_ID << "\n";
            writeBasic(file);
        }
};