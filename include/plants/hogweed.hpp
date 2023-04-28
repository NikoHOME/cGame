
#include "world.hpp"
#include "plant.hpp"

class SosnowskyHogweed : public Plant
{   
    public:
        SosnowskyHogweed(int x, int y) : Plant(10,0,x,y) {}
        const char *getChar() const 
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(HOGWEED_COLOUR)); 
            return "H";
        }
        const char *getName() const {return "Sosnowsky hogweed";}
        virtual const char *getKillMessage() const { return "burned";}
        void action();
        CollisionAction collision();
        SosnowskyHogweed *reproduce(int x, int y) 
        {
            return new SosnowskyHogweed(x,y);
        }
        void write(std::ofstream &file)
        {
            file << HOGWEED_ID << "\n";
            writeBasic(file);
        }
};