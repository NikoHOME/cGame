#include "world.hpp"
#include "animal.hpp"

class Fox : public Animal
{  

    public:
        Fox(int x, int y) : Animal(3,7,x,y) {}
        const char *getChar() const 
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(FOX_COLOUR)); 
            return "F";
        }
        const char *getName() const {return "Fox";}
        virtual const char *getKillMessage() const override {return "scratched";}
        void action();
        bool isSameSpecies(Organism *animal)
        {
            auto mate = dynamic_cast<Fox *>(animal);
            if (!mate) return false;
            return true;
        }
        Fox *reproduce(int x,int y) 
        { 
            return new Fox(x,y);
        }
        void write(std::ofstream &file)
        {
            file << FOX_ID << "\n";
            writeBasic(file);
        }
};