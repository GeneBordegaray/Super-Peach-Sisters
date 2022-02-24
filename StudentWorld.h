#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include "Level.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();

    virtual int init();
    virtual int move();
    virtual void cleanUp();

    bool createLevel(int lev);

    bool* isBlockedPath(Actor *player, bool amountTrue[4]);
    bool overLapBadGuy(Actor* player);

private:
    //maintain the list of actors: //blocks
   Peach* m_peach;

   std:: vector<Actor*> actorList;
};


#endif // STUDENTWORLD_H_
