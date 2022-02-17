#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
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
{}


int StudentWorld::init()
{
    createLevel();
    return GWSTATUS_CONTINUE_GAME;
}


int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    m_peach->doSomething();
    //decLives();

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
}

void StudentWorld::createLevel()
{
    actorList.clear();

    Level curLev(assetPath());
    string level_file = "level01.txt";
    Level::LoadResult result = curLev.loadLevel(level_file);

    if (result == Level::load_fail_file_not_found)
    {
        cerr << "Could not find level01.txt data file" << endl;
    }
    else if (result == Level::load_fail_bad_format)
    {
        cerr << "level01.txt is improperly formatted" << endl;
    }
    else if (result == Level::load_success)
    {
        cerr << "Successfully loaded level" << endl;
        Level::GridEntry mapEntry;
        for (int x = 0; x < 256; x++)
            for (int y = 0; y < 256; y++)
            {
                mapEntry = curLev.getContentsOf(x, y);
                
                Actor* ptr;
                switch (mapEntry)
                {

                case Level::block:
                    ptr = new Block(this, IID_BLOCK, 8*x, 8*y, 1, 1, 1);
                    actorList.push_back(ptr);
                    break;

                case Level::peach:
                    ptr = new Peach(this, IID_PEACH, 8 * x, 8 * y, 1, 1, 1);
                    actorList.push_back(ptr);
                    break;
                }
            }
    }
}
