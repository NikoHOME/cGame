
#include "manager.hpp"
#include "animals.hpp"
#include "plants.hpp"
#include <queue>
#include "organism.hpp"
#include <fstream>
#include <dirent.h>

#define ABILITY_COOLDOWN 10
#define ABILITY_DURATION 5

void Manager::initializeCurses()
{
    initscr();
    cbreak();
    noecho();
    refresh();
	curs_set(0);
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);

    start_color();
    use_default_colors();
    init_pair(BASIC_COLOUR, COLOR_WHITE, COLOR_BLACK);

    init_pair(WOLF_COLOUR, COLOR_BLACK+8, COLOR_BLACK);
    init_pair(FOX_COLOUR, COLOR_RED+8, COLOR_BLACK);
    init_pair(SHEEP_COLOUR, COLOR_WHITE, COLOR_BLACK);
    init_pair(TURTLE_COLOUR, COLOR_GREEN, COLOR_BLACK);
    init_pair(ANTILOPE_COLOUR, COLOR_RED, COLOR_BLACK);

    init_pair(GRASS_COLOUR, COLOR_GREEN+8, COLOR_BLACK);
    init_pair(GUARANA_COLOUR, COLOR_MAGENTA+8, COLOR_BLACK);
    init_pair(BELLADONA_COLOUR, COLOR_BLUE, COLOR_BLACK);
    init_pair(HOGWEED_COLOUR, COLOR_CYAN, COLOR_BLACK);
    init_pair(DANDELION_COLOUR, COLOR_YELLOW, COLOR_BLACK);

    init_pair(PLAYER_COLOUR, COLOR_BLACK, COLOR_WHITE);


	//Turn off ESC delay
	ESCDELAY = 25;

}

void Manager::initializeMessageWindow()
{

	//maxBoardsize used in custom board size
	int maxy,maxx,maxBoardSize;
	getmaxyx(stdscr,maxy,maxx);

	messageWindow = newwin(20, 40, (maxy-20)/2+10, 10);
    box(messageWindow, 0, 0);
    
    refresh();
	wrefresh(messageWindow);

}

#define MAX_DIGITS 2
#define CONFIRM_KEY '\n'
#define DEFAULT_SIZE 20

int getInputNumber()
{
    char inputArray[5];
    inputArray[0] = '\0';
    int key;
    int inputSize=0;
    while((key = getch()) != QUIT_KEY)
    {
        switch(key)
        {
            case '1' ... '9':
                if(inputSize == MAX_DIGITS)
                    break;
                inputArray[inputSize] = key;
                ++inputSize;
                inputArray[inputSize] = '\0';
                break;
            case '0':
                if(inputSize == MAX_DIGITS)
                    break;
                if(inputSize == 0)
                    break;
                inputArray[inputSize] = key;
                ++inputSize;
                inputArray[inputSize] = '\0';             
                break;
            case KEY_BACKSPACE:
                if(inputSize == 0)
                    break;
                --inputSize;
                inputArray[inputSize] = '\0';
                break;
            case CONFIRM_KEY:
                int output = std::atoi(inputArray);
                if(output < 10)
                {  
                    mvprintw(13,10,"Size too small");
                    refresh();
                    break;
                }
                if(output > 50)
                {  
                    mvprintw(13,10,"Size too big ");
                    refresh();
                    break;
                }
                return output;
                break;
        }
        mvprintw(11,10,"   ");
        mvprintw(11,10,"%s",inputArray);
        refresh();
    }
    return DEFAULT_SIZE;
}


void Manager::inputWorldSize()
{
    mvprintw(10,10,"Board Height:");
    mvprintw(11,10,"   ");
    refresh();

    worldHeight = getInputNumber();


    mvprintw(10,10,"Board Width:");
    mvprintw(11,10,"   ");
    refresh();

    worldWidth = getInputNumber();

    clear();
    mvprintw(0,10,"Height: %d Width: %d",worldHeight,worldWidth);
    refresh();

    world = new World(worldHeight, worldWidth);


    world->setManager(this);
    world->initializeWindow();
    world->draw();
}
bool Manager::handleInput()
{
    int key = wgetch(world->getWindow());
    switch(key)
    {
        case KEY_UP:
            world->getRefPlayerAction() = MOVE_UP;
            break;
        case KEY_LEFT:
            world->getRefPlayerAction() = MOVE_LEFT;
            break;
        case KEY_DOWN:
            world->getRefPlayerAction() = MOVE_DOWN;
            break;
        case KEY_RIGHT:
            world->getRefPlayerAction() = MOVE_RIGHT;
            break;
        case NEXT_TURN:
            world->getRefPlayerAction() = NEXT_TURN;
            break;
        case USE_ABILITY:
            world->getRefPlayerAction() = USE_ABILITY;
            break;
        case SAVE_KEY:
            if(world->getRefPlayerAction() == SAVE_KEY)
                break;
            world->getRefPlayerAction() = SAVE_KEY;
            saveInput();
            break;
        case LOAD_KEY:
            world->getRefPlayerAction() = LOAD_KEY;
            loadInput();
            break;
        case QUIT_KEY:
            return false;
            break;
    }
    return true;
}

void Manager::processInput()
{
    int playerPosX = world->getPlayerPosX();
    int playerPosY = world->getPlayerPosY();

    bool playerAlive = world->getPlayerAliveStatus(); 
    char playerInput = world->getPlayerAction();

    Player *player = dynamic_cast<Player *>(world->getOrganismDisplay()[playerPosX][playerPosY]);
    if(!player) playerAlive = false;
    switch(playerInput)
    {
        case MOVE_UP: case MOVE_DOWN: case MOVE_LEFT: case MOVE_RIGHT:
            if(!playerAlive)
                break;
            if(!player->inputAction())
                break;
            world->nextTurn();
            printMessages();
            world->draw();
            break;
        case NEXT_TURN:
            world->nextTurn();
            printMessages();
            world->draw();
            break;
        case USE_ABILITY:
            if(!playerAlive)
                break;
            if(!world->playerCanUseAbility())
                break;
            world->getRefLastTimeAbilityUsed() = world->getTurn();
            world->getRefgAbilityDuration() = ABILITY_DURATION;
            if(world->playerCanUseAbility())
                mvprintw(6,10,"O Ability avaible    ");
            else
                mvprintw(6,10,"X Ability not avaible");
            if(world->playerHasAbility())
                mvprintw(8,10,"O Ability duration: %d",world->getRefgAbilityDuration());
            else
                mvprintw(8,10,"X Ability duration: %d",world->getRefgAbilityDuration());
            world->draw();
            refresh();
            break;
    }
}

#define MAX_FILENAME_SIZE 32

bool isspace(char c)
{
    if(c==' ' || c=='\n' || c== '\r' || c=='\t')
        return true;
    return false;
}

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}


void Manager::printMessages()
{
    wclear(messageWindow);
    wrefresh(messageWindow);
    refresh();
    int textRow = 1;
    while(!messages.empty())
    {
        Message message = messages.front();
        messages.pop();
        mvwprintw(messageWindow,textRow,1,"%s %s %s",message.animal1, message.message, message.animal2);
        ++textRow;
    }
    box(messageWindow, 0, 0);
    wrefresh(messageWindow);
    refresh();
}

void Manager::pushMessage(Message message)
{
    messages.push(message);
}


void Manager::saveInput()
{
    char timef[MAX_FILENAME_SIZE+1], inputf[MAX_FILENAME_SIZE+1];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(timef, "%02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
    snprintf(inputf, sizeof(inputf), "save/%s.save", trim(timef));

    mvprintw(20,10,"File saved as %s",inputf);
    refresh();
    clear();

    saveWorld(inputf);
}

#define PER_PAGE 15

void drawLoad(WINDOW *window,char *input[],int select, int fileNumber)
{
    clear();
    int index, indexEnd, offset = 40, perPage = PER_PAGE;
    char namef[MAX_FILENAME_SIZE+1];
    //Paging calculation
    index = (select / perPage) * perPage;
    indexEnd = index + perPage; 
    mvprintw(4,10,"Load a game");
    refresh();


    //Paging selection
    for(;index < indexEnd && index < fileNumber; ++index)
    {
        sprintf(namef, "%d: %s", index, input[index]);
        attron(COLOR_PAIR(BASIC_COLOUR));
        attroff(COLOR_PAIR(PLAYER_COLOUR));
        if(index == select)
        {   
            attroff(COLOR_PAIR(BASIC_COLOUR));
            attron(COLOR_PAIR(PLAYER_COLOUR));
        }
        mvprintw(index%PER_PAGE+5,10,"%s",namef);
        //drawString(gfx->renderer, SCREEN_WIDTH/2 - strlen(namef)*TEXT_SIZE/2, TEXT_SIZE*9 +offset, namef, gfx->scrtex, 1, 1);
    }
    refresh();
    //SDL_RenderPresent(gfx->renderer);    
}

void Manager::loadInput()
{
    

    DIR *dir = opendir("./save");
    struct dirent *read;
    int fileNumber = 0, index = 0;
    while((read = readdir(dir)) != NULL) 
    {
        if ( !strcmp(read->d_name, ".") || !strcmp(read->d_name, "..") )
            continue;
        ++fileNumber;
    }
    rewinddir(dir);
    char *filesList[fileNumber];
    while((read = readdir(dir)) != NULL) {
        if ( !strcmp(read->d_name, ".") || !strcmp(read->d_name, "..") )
            continue;
        filesList[index] = (char*) malloc (strlen(read->d_name)+1);
        strncpy (filesList[index],read->d_name, strlen(read->d_name) );
        filesList[index] = read->d_name;
        ++index;
    }
    rewinddir(dir);

    if(fileNumber == 0)
        return;

    wclear(world->getWindow());
    clear();
    wrefresh(world->getWindow());
    refresh();

    drawLoad(world->getWindow(), filesList, 0, fileNumber);

    int select = 0;
    int key = 0;
    //Create load menu
    while(key != CONFIRM_KEY)
    {
        key = wgetch(world->getWindow());
		switch(key) 
        {
            case KEY_UP:
                if(!fileNumber)
                    break;
                if(select > 0)
                    --select;
                drawLoad(world->getWindow(), filesList, select, fileNumber);
                break;
            case KEY_DOWN:
                if(!fileNumber)
                    break;
                if(select < fileNumber-1)
                    ++select;
                drawLoad(world->getWindow(), filesList, select, fileNumber);                    
                break;           
        }
    } 
    char inputf[MAX_FILENAME_SIZE+1];
    
    if(fileNumber)
    {
        snprintf(inputf, sizeof(inputf), "save/%s", filesList[select]);
        loadWorld(inputf);
    }
}





void Manager::saveWorld(const char name[])
{
    std::ofstream file;
    file.open(name);

    WorldData data = world->getWorldData();
    file << data.boardSize.height << " " << data.boardSize.width << "\n";
    file << data.AbilityDuration << " " << data.lastTimeAbilityUsed << "\n";
    file << data.newAnimalIndex << " " << data.turn << "\n"; 
    file << data.playerPosX << " " << data.playerPosY << "\n";
    file << (int)data.playerInput << " " << (int)data.playerAlive << "\n";
    
    int organismAmmount = 0;
    std::queue <Organism *> organismQue; 

    for(int i = 0; i < data.boardSize.width; ++i)
    {
        for(int j = 0; j < data.boardSize.height; ++j)
        {
            if(world->getOrganismDisplay()[i][j] != nullptr)
            {
                ++organismAmmount;
                organismQue.push(world->getOrganismDisplay()[i][j]);
            }
        }
    }
    file << organismAmmount << "\n";
    while(!organismQue.empty())
    {
        Organism *nextOrganism = organismQue.front();
        organismQue.pop();
        
        nextOrganism->write(file);
    }

    file.close();
}

void Manager::loadWorld(const char name[])
{
    std::ifstream file;
    file.open(name);

    WorldData data;
    file >> data.boardSize.height >> data.boardSize.width;
    file >> data.AbilityDuration >> data.lastTimeAbilityUsed;
    file >> data.newAnimalIndex >> data.turn;
    file >> data.playerPosX >> data.playerPosY;
    int temporaryInt1, temporaryInt2;
    file >> temporaryInt1 >> temporaryInt2;
    data.playerInput = temporaryInt1;
    data.playerAlive = temporaryInt2;
    /*
    fscanf(file,"%d %d\n",&data.boardSize.height,&data.boardSize.width);
    fscanf(file,"%d %d ",&data.AbilityDuration,&data.lastTimeAbilityUsed);
    fscanf(file,"%d %d ",&data.newAnimalIndex,&data.turn);
    fscanf(file,"%d %d ",&data.playerPosX,&data.playerPosY);
    fscanf(file,"%d %d\n",&data.playerInput,&data.playerAlive);
    */
    int organismAmmount;
    file >> organismAmmount;
    //fscanf(file,"%d\n",&organismAmmount);

    delwin(world->getWindow());
    clear();
    refresh();

    world = new World(data.boardSize.height, data.boardSize.width, true);
    world->setWorldData(data);
    world->setManager(this);

    int id;
    int strength;
    int innitiative;
    int positionX,positionY;
    int index;

    Organism* newOrganism;

    for(int i = 0 ;i < organismAmmount; ++i)
    {
        file >> id;
        //fscanf(file,"%d\n",&id);
        file >> strength >> innitiative >> positionX >> positionY >> index;
        //fscanf(file,"%d %d %d %d %d\n",&strength,&innitiative,&positionX,&positionY,&index);
        switch(id)
        {
            case WOLF_ID:
                newOrganism = new Wolf(positionX,positionY);
                break;
            case SHEEP_ID:
                newOrganism = new Sheep(positionX,positionY);
                break;
            case TURTLE_ID:
                newOrganism = new Turtle(positionX,positionY);
                break;
            case ANTILOPE_ID:
                newOrganism = new Antilope(positionX,positionY);
                break;
            case FOX_ID:
                newOrganism = new Fox(positionX,positionY);
                break;
            case PLAYER_ID:
                newOrganism = new Player(positionX,positionY);
                break;
            case GRASS_ID:
                newOrganism = new Grass(positionX,positionY);
                break;
            case DANDELION_ID:
                newOrganism = new Dandelion(positionX,positionY);
                break;
            case GUARANA_ID:
                newOrganism = new Guarana(positionX,positionY);
                break;
            case BELLADONA_ID:
                newOrganism = new Belladonna(positionX,positionY);
                break;
            case HOGWEED_ID:
                newOrganism = new SosnowskyHogweed(positionX,positionY);
                break;
        }
        newOrganism->setStrength(strength);
        newOrganism->setInnitiative(innitiative);
        newOrganism->setIndex(index);
        newOrganism->setWorld(world);
        world->getOrganismDisplay()[positionX][positionY] = newOrganism;
    }

    world->initializeWindow();
    world->draw();

    file.close();
}
