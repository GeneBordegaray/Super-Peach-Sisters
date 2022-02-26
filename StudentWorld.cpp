#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <cmath>
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
    m_hp = 3;
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
    //is peach alive
    if (m_peach->isAlive())
    {
        m_peach->doSomething();
        //still alive after doing soemthing?
        if (!m_peach->isAlive())
        {
            //decrease how many lives peach has
            decLives();
            playSound(SOUND_PLAYER_DIE);
            return GWSTATUS_PLAYER_DIED;
        }
    }
    else
    {
        playSound(SOUND_PLAYER_DIE);
        return GWSTATUS_PLAYER_DIED;
    }

    //telling all actors in vector to do something
    vector<Actor*>::iterator it;
    for (it = actorList.begin(); it != actorList.end(); it++)
    {
        //actor has to be alive to do something
        if ((*it)->isAlive())
        {
            (*it)->doSomething();
            if (!m_peach->isAlive())
            {
                decLives();
                return GWSTATUS_PLAYER_DIED;
            }
        }
    }

    //removing all the dead actors
    for (it = actorList.begin(); it != actorList.end();)
    {
        if (!(*it)->isAlive())
        {
            delete* it;
            it = actorList.erase(it);
        }
        //if alive then continue through the vector
        else
        {
            it++;
        }
    }

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
                    ptr = new Block(this, IID_BLOCK, SPRITE_WIDTH * x, SPRITE_HEIGHT * y, 0, 2, 1.0, Block::none);
                    actorList.push_back(ptr);
                    break;

                case Level::flower_goodie_block:
                    ptr = new Block(this, IID_BLOCK, SPRITE_WIDTH * x, SPRITE_HEIGHT * y, 0, 2, 1.0, Block::flower);
                    actorList.push_back(ptr);
                    break;

                case Level::mushroom_goodie_block:
                    ptr = new Block(this, IID_BLOCK, SPRITE_WIDTH * x, SPRITE_HEIGHT * y, 0, 2, 1.0, Block::mushroom);
                    actorList.push_back(ptr);
                    break;

                case Level::star_goodie_block:
                    ptr = new Block(this, IID_BLOCK, SPRITE_WIDTH * x, SPRITE_HEIGHT * y, 0, 2, 1.0, Block::star);
                    actorList.push_back(ptr);
                    break;

                case Level::pipe:
                    ptr = new Pipe(this, IID_PIPE, SPRITE_WIDTH * x, SPRITE_HEIGHT * y, 0, 2, 1.0);
                    actorList.push_back(ptr);
                    break;

                case Level::goomba:
                    ptr = new Goomba(this, IID_GOOMBA, SPRITE_WIDTH * x, SPRITE_HEIGHT * y, (rand() > RAND_MAX / 2) ? 0 : 180, 0, 1.0);
                    actorList.push_back(ptr);
                    break;
                }
            }
        return true;
    }
    return false;
}


void StudentWorld::addGoodie(Block* a)
{
    Actor* goodie;
    
    //get the blocks coords
    int blockX = int(a->getX());
    int blockY = int(a->getY());

    //what type of goodie
    switch(a->getGoodieType())
    {
        //mushroom
    case 1:
        goodie = new Mushroom(this, IID_MUSHROOM, blockX, blockY + 8, 0, 1, 1.0);
        actorList.push_back(goodie);
        break;

    default:
        break;
    }

    return;
}

bool StudentWorld::overlap(double ax, double ay, double bx, double by) const
{
    //checking overlapping between the two actor's coord parameters
    if (abs(ax - bx) < SPRITE_WIDTH && abs(ay - by) < SPRITE_HEIGHT)
    {
        return true;
    }
    return false;
}

bool StudentWorld::overlapPeach(Actor* a) const
{
    //get peaches coords
    double peachX = m_peach->getX();
    double peachY = m_peach->getY();

    //get parameter object's coords
    double objectX = a->getX();
    double objectY = a->getY();

    if (overlap(peachX, peachY, objectX, objectY))
    {
        return true;
    }
    return false;
}

bool StudentWorld::overlapPeach() const
{
    vector<Actor*>::const_iterator it;
    for (it = actorList.begin(); it != actorList.end(); it++)
    {
        if (overlapPeach(*it))
        {
            return true;
        }
    }
    return false;
}

bool StudentWorld::canMoveThere(Actor* player, double ax, double ay) const
{
    vector<Actor*>::const_iterator it;
    for (it = actorList.begin(); it != actorList.end(); it++) 
    {
        //get the object that it is pointing to's coords
        double bx = (*it)->getX();
        double by = (*it)->getY();
        
        //is it pointing to itself
        if ((*it) == player)
        {
            continue;
        }

        //does this object block?
        if ((*it)->canBlock())
        {
            if (overlap(ax, ay, bx, by))
            {
                return false;
            }
        }
    }
    return true;
}


bool StudentWorld::moveOrBonk(Actor* player, double ax, double ay) const
{
    //check if player is moving to valid position
    if (canMoveThere(player, ax, ay))
    {
        player->moveTo(ax, ay);
        return true;
    }
    else
    {
        vector<Actor*>::const_iterator it;
        for (it = actorList.begin(); it != actorList.end(); it++)
        {
            //Get coords that it is pointing to
            double itX = (*it)->getX();
            double itY = (*it)->getY();

            //is the object overlap with peach
            if (overlap(ax, ay, itX, itY))
            {
                (*it)->bonk();
            }
        }
        return false;
    }
}

bool StudentWorld::bonkOverlappingPeach(Actor* bonker) const
{
    //is the bonker and peach touching
    if (overlapPeach(bonker))
    {
        m_peach->bonk();
        return true;
    }
    return false;
}

bool StudentWorld::bonkOverlappingActor(Actor* bonker) const
{
    //get the bonkers coords
    double bonkerX = bonker->getX();
    double bonkerY = bonker->getY();

    vector<Actor*>::const_iterator it;
    for (it = actorList.begin(); it != actorList.end(); it++)
    {
        //get its coords
        double bx = (*it)->getX();
        double by = (*it)->getY();

        //do they touch
        if (overlap(bonkerX, bonkerY, bx, by))
        {
            (*it)->bonk();
            return true;
        }
    }
    return false;
}

//set peaches hp to whatever it needs to be
void StudentWorld::setPeachHP(int hp) const
{
    m_peach->setHP(hp);
}

//give peach muchroom power
void StudentWorld::grantJumpPower() const
{
    m_peach->setHasMushroom(true);
}
