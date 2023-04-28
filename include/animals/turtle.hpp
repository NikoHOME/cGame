#include "world.hpp"
#include "animal.hpp"

class Turtle : public Animal
{  
    public:
        Turtle(int x, int y) : Animal(2,1,x,y) {}
        const char *getChar() const 
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(TURTLE_COLOUR)); 
            return "T";
        }
        const char *getName() const {return "Turtle";}
        virtual const char *getKillMessage() const {return "bumped into";}
        void action();
        CollisionAction collision();
        bool isSameSpecies(Organism *animal)
        {
            auto mate = dynamic_cast<Turtle *>(animal);
            if (!mate) return false;
            return true;
        }
        Turtle *reproduce(int x,int y) 
        {
            return new Turtle(x,y);
        }
        void write(std::ofstream &file)
        {
            file << TURTLE_ID << "\n";
            writeBasic(file);
        }
};