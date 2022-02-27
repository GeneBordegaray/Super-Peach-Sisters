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

    //add a mushroom to the world
    void addMushroom(double ax, double ay);

    //add a flower to the world
    void addFlower(double ax, double ay);

    //add a peachfire ball to the game
    void addPeachFireball(double ax, double ay, int PeachDirec);

    //are two actors touching
    bool overlap(double ax, double ay, double bx, double by) const;

    //is an object touching peach
    bool overlapPeach(Actor* a) const;
    bool overlapPeach() const;

    //can peach move there
    bool canMoveThere(Actor* player, double ax, double ay) const;

    //should actor move there or bonk it
    bool moveOrBonk(Actor* player, double ax, double ay) const;

    //bonk overlapping characters with peach
    bool bonkOverlappingPeach(Actor* bonker) const;

    //bonk other things
    //Peach is always the bonker
    bool bonkOverlappingActor(Actor* bonker) const;

    //overlapping with damageable object
    bool damageOverlappingActor(Actor* damage) const;

    //Setting peach hp
    void setPeachHP(int hp) const;

    //give peach jump power
    void grantJumpPower() const;

    //give peach flower power
    void grantShootingPower() const;

private:
    //my peach character
    Peach* m_peach;
    int m_hp;

    //keep track of all the actors in the game
    std::vector<Actor*> actorList;
};


#endif // STUDENTWORLD_H_
