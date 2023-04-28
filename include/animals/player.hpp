
#include "world.hpp"
#include "animal.hpp"

class Player : public Animal
{
    public:
        Player(int x,int y) : Animal(5,4,x,y) {}
        const char *getChar() const 
        {
            wattroff(world->getWindow(), COLOR_PAIR(BASIC_COLOUR));
            wattron(world->getWindow(), COLOR_PAIR(PLAYER_COLOUR)); 
            return "@";
        }
        const char *getName() const {return "Player";}
        virtual const char *getKillMessage() const {return "slashed";}
        bool inputAction();
        void action();
        CollisionAction collision();
        bool isSameSpecies(Organism *animal) { return false;}
        Player *reproduce(int x,int y) { return this;}      
        void write(std::ofstream &file)
        {
            file << PLAYER_ID << "\n";
            writeBasic(file);
        }
};