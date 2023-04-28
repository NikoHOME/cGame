#include "world.hpp"
#include "animal.hpp"

class Sheep : public Animal
{  
    public:
        Sheep(int x, int y) : Animal(4,4,x,y) {}
        const char *getChar() const 
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(SHEEP_COLOUR)); 
            return "S";
        }
        const char *getName() const {return "Sheep";}
        virtual const char *getKillMessage() const {return "trampled";}
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
        void write(std::ofstream &file)
        {
            file << SHEEP_ID << "\n";
            writeBasic(file);
        }
};