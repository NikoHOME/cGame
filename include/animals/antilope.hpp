#include "world.hpp"
#include "animal.hpp"

class Antilope : public Animal
{  

    public:
        Antilope(int x, int y) : Animal(4,4,x,y) {}
        const char *getChar() const
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(ANTILOPE_COLOUR)); 
            return "A";
        }
        const char *getName() const {return "Antilope";}
        const char *getKillMessage() const {return "stomped";}
        void action();
        CollisionAction collision();
        bool isSameSpecies(Organism *animal)
        {
            auto mate = dynamic_cast<Antilope *>(animal);
            if (!mate) return false;
            return true;
        }
        Antilope *reproduce(int x, int y) 
        {
            return new Antilope(x,y);
        }
        void write(std::ofstream &file)
        {
            file << ANTILOPE_ID << "\n";
            writeBasic(file);
        }
};