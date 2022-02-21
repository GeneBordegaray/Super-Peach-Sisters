#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;

/*****Base Actor*****/
class Actor : public GraphObject
{
public:

    Actor(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);
    virtual ~Actor();

    virtual void doSomething() = 0;

	virtual bool canBlock();

	StudentWorld* getWorld() const;

private:
	StudentWorld* m_world;
};

/*****Stationary Actor Base Class*****/
class stationaryActors : public Actor
{
public:
	stationaryActors(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);
	virtual ~stationaryActors();

	virtual bool canBlock();

private:

};


/*****Block*****/
class Block : public stationaryActors
{
public:

	Block(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);
	virtual ~Block();

	virtual void doSomething();
};

/*****Peach Class*****/
class Peach : public Actor
{
public:

	Peach(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);
	virtual ~Peach();

	bool isAlive();
	void setHP(int hp);
	int getHP();

	virtual void doSomething();

private:
	int m_hp;
};
/*
class StudentWorld;

class Actor : public GraphObject
{
public:
	Actor(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size); //Actor Constructor
	virtual ~Actor();

	virtual void doSomething() = 0; //what the character is doing per tick
	
	virtual bool isAlive() const; //check that teh actor is alive per tick
	void dead(); //sets to dead is run out of lives

	//virtual bool canBeHit(); //check if can be hit by fireball
	//virtual bool canBeEaten(); // check if peach can eat 

	StudentWorld* getWorld() const;

private:
	bool m_alive;
	StudentWorld* m_world;
};


class Peach : public Actor
{
public:
	Peach(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size);
	virtual ~Peach();

	virtual void doSomething();

	void setHP(int hp);
	int getHP() const;

private:
	int m_hp;
};
*/
#endif // ACTOR_H_
