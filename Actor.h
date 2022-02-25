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

	virtual void bonk() = 0;

	virtual bool canBlock();
	virtual bool doesDamage();
	virtual bool isAlive();

	StudentWorld* getWorld() const;

private:
	StudentWorld* m_world;
	bool m_alive;
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



/*****Bad Guy Actor Class*****/
class BadGuy : public Actor
{
public:
	BadGuy(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);
	virtual ~BadGuy();

	virtual bool doesDamage();

private:

};




/*****Block*****/
class Block : public stationaryActors
{
public:

	Block(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);
	virtual ~Block();

	virtual void doSomething();
	virtual void bonk();
};


/*****Pipes*****/
class Pipe : public stationaryActors
{
public:

	Pipe(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);
	virtual ~Pipe();

	virtual void doSomething();
	virtual void bonk();
};

/*****Peach Class*****/
class Peach : public Actor
{
public:

	Peach(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);
	virtual ~Peach();

	virtual bool isAlive();
	void setHP(int hp);
	int getHP();
	void decHP();

	int getJumpPower();
	void setJumpPower(int remaining_jump_power);
	void decJumpPower();

	virtual void doSomething();
	virtual void bonk();

private:
	int m_hp;
	int remaining_jump_power;
};


#endif // ACTOR_H_
