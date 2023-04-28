#pragma once
#include "world.hpp"
#include <queue>

#define WOLF_COLOUR 1
#define SHEEP_COLOUR 2
#define FOX_COLOUR 3
#define TURTLE_COLOUR 5
#define ANTILOPE_COLOUR 6

#define GRASS_COLOUR 7
#define DANDELION_COLOUR 8
#define BELLADONA_COLOUR 9
#define HOGWEED_COLOUR 10
#define GUARANA_COLOUR 11

#define PLAYER_COLOUR 12

#define BASIC_COLOUR 13


#define MOVE_UP 11
#define MOVE_DOWN 12
#define MOVE_LEFT 13
#define MOVE_RIGHT 14

#define QUIT_KEY 'q'    //Control Keys
#define NEXT_TURN 'n'
#define USE_ABILITY 'e'
#define SAVE_KEY 's'
#define LOAD_KEY 'l'

struct Message
{
    const char *animal1, *animal2, *message;
};


class Manager
{
    Manager *manager;
    WINDOW *messageWindow;
    World *world;
    int worldHeight = 0;
    int worldWidth = 0;
    std::queue <Message> messages;
    public:
        void inputWorldSize();
        bool handleInput();
        void processInput();
        void setWorld(World *inWorld) { world = inWorld;}
        void saveInput();
        void loadInput();
        void saveWorld(const char name[]);
        void loadWorld(const char name[]);
        void printMessages();
        void pushMessage(Message message);
        void initializeMessageWindow();
        void initializeCurses();
};