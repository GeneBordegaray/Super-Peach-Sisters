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

    bool overlap(double ax, double ay, double bx, double by) const;
    bool overlapPeach(Actor* a) const;
    bool canMoveThere(Actor* player, double ax, double ay) const;
    bool moveOrBonk(Actor* player, double ax, double ay) const;

private:
    //maintain the list of actors: //blocks
    Peach* m_peach;

    std::vector<Actor*> actorList;
};


#endif // STUDENTWORLD_H_
