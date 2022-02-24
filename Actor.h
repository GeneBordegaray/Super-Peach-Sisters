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

/*****Bad Guy Base Class*****/
class badGuy : public Actor
{
public:
	badGuy(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);
	virtual ~badGuy();

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


/*****Pipes*****/
class Pipe : public stationaryActors
{
public:

	Pipe(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);
	virtual ~Pipe();

	virtual void doSomething();
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

	int getJumpPower();
	void setJumpPower(int remaining_jump_power);
	void decJumpPower();

	virtual void doSomething();

private:
	int m_hp;
	int remaining_jump_power;
};

/*****Goomba Class*****/
class Goomba : public badGuy
{
public:
	Goomba(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);
	virtual ~Goomba();

	virtual void doSomething();

private:

};

#endif // ACTOR_H_
