#include "world.hpp"
#include "plant.hpp"

class Belladonna : public Plant
{   
    public:
        Belladonna(int x, int y) : Plant(99,0,x,y) {}
        const char *getChar() const 
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(BELLADONA_COLOUR)); 
            return "B";
        }
        const char *getName() const {return "Belladonna";}
        virtual const char *getKillMessage() const {return "got tasted by";}
        CollisionAction collision();
        Belladonna *reproduce(int x, int y) 
        {
            return new Belladonna(x,y);
        }
        void write(std::ofstream &file)
        {
            file << BELLADONA_ID << "\n";
            writeBasic(file);
        }
};