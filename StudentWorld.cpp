#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_peach = nullptr;
}
StudentWorld::~StudentWorld()
{
    cleanUp();
}


int StudentWorld::init()
{
    if (getLevel() > 99)
    {
        return GWSTATUS_PLAYER_WON;
    }
    if (createLevel(getLevel()) == false)
    {
        return GWSTATUS_LEVEL_ERROR;
    }

    return GWSTATUS_CONTINUE_GAME;
}


int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    m_peach->doSomething();

    vector<Actor*>::iterator it;
    for (it = actorList.begin(); it != actorList.end(); it++) //telling all actors in vector to do something
    {
        (*it)->doSomething();
    }
   
   // decLives();

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete m_peach; //delteing main character
    m_peach = nullptr;

    vector<Actor*>::iterator it;
    for (it = actorList.begin(); it != actorList.end(); it++) //deleteing all actors in vector
    {
        delete* it;
        it = actorList.erase(it);
    }
    actorList.clear(); //clearing vector
}

bool StudentWorld::createLevel(int lev)
{
    actorList.clear();

    stringstream str;
    str << "level" << setfill('0') << setw(2) << lev; //setting proper level number
    string str2 = str.str();

    Level curLev(assetPath());
    Level::LoadResult result = curLev.loadLevel(str2 + ".txt"); //getting proper level contents

    if (result == Level::load_fail_file_not_found)
    {
        cerr << "Could not find level01.txt data file" << endl;
        return false;
    }
    else if (result == Level::load_fail_bad_format)
    {
        cerr << "level01.txt is improperly formatted" << endl;
        return false;
    }
    else if (result == Level::load_success)
    {
        cerr << "Successfully loaded level" << endl;
        Level::GridEntry mapEntry;
        for (int x = 0; x < VIEW_WIDTH; x++) //iterating through text file
            for (int y = 0; y < VIEW_HEIGHT; y++)
            {
                mapEntry = curLev.getContentsOf(x, y);
                //making new actors based off the charaters found in the level.txt file
                Actor* ptr;
                switch (mapEntry)
                {
                case Level::empty:
                    break;

                case Level::peach:
                    m_peach = new Peach(this, IID_PEACH, SPRITE_WIDTH * x, SPRITE_HEIGHT * y, 0, 0, 1.0);
                    break;

                case Level::block:
                    ptr = new Block(this, IID_BLOCK, SPRITE_WIDTH * x, SPRITE_HEIGHT * y, 0, 2, 1.0);
                    actorList.push_back(ptr);
                    break;
                    /*
                case Level::pipe:
                    ptr = new Pipe(this, IID_PIPE, SPRITE_WIDTH * x, SPRITE_HEIGHT * y, 0, 2, 1.0);
                    actorList.push_back(ptr);
                    break;
                    */
                }
            }
        return true;
    }
    return false;
}

bool* StudentWorld::isBlockedPath(Actor *player)
{
    bool amountTrue[4] = { false, false, false, false };
    vector<Actor*>::iterator it;
    for (it = actorList.begin(); it != actorList.end(); it++) //iterating through actor vector
    {
        if (*it == player)
        {
            continue;
        }
        
        double checkObjectX = (*it)->getX(); 
        double checkObjectY = (*it)->getY();

        if (player->getDirection() == 0)
        {
            //east
            if (player->getX() + 4 == checkObjectX - 4  && (player->getY() == checkObjectY || player->getY() == checkObjectY + 4 || player->getY() + 4 == checkObjectY)) //checking to see if peach has run into an object
            {
                if ((*it)->canBlock()) //checking if that object blocks other objects
                {
                    amountTrue[2] = true;

                }
            }
        }

        if (player->getDirection() == 180)
        {
            if (player->getX() - 4 == checkObjectX + 4 && (player->getY() == checkObjectY || player->getY() == checkObjectY + 4 || player->getY() + 4 == checkObjectY)) //checking to see if peach has run into an object
            {
                //west
                if ((*it)->canBlock()) //checking if that object blocks other objects
                {
                    amountTrue[3] = true;

                }
            }
        }

        if (player->getY() + 4 == checkObjectY - 4 && ((player->getX() == checkObjectX || player->getX() == checkObjectX + 4 || player->getX() + 4 == checkObjectX)))
        {
            amountTrue[0] = true;
        }
        if (player->getY() - 4 == checkObjectY + 4 && ((player->getX() == checkObjectX || player->getX() == checkObjectX + 4 || player->getX() + 4 == checkObjectX)))
        {
            amountTrue[1] = true;
        }
    }
    return amountTrue;
}
