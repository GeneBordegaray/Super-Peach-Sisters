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

	//what to do each tick
	void doSomething();

	//get bonked
	virtual void bonk();

	//is this a character that prevents movement
	virtual bool canBlock() const;

	//what to do when you are supposed to get damaged
	virtual void sufferDamage();

	//is the character alive
	bool isAlive() const;
	void setDead();

	//turn the character around
	void reverseActor();

	StudentWorld* getWorld() const;

private:
	virtual void doSomethingUnique() = 0;
	StudentWorld* m_world;
	bool m_alive;
};

/*****Stationary Actor Base Class*****/
class stationaryActors : public Actor
{
public:
	stationaryActors(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);
	virtual ~stationaryActors();

	virtual bool canBlock() const;
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

	virtual void bonk();

private:
	virtual void doSomethingUnique();
};


/*****Pipes*****/
class Pipe : public stationaryActors
{
public:

	Pipe(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);
	virtual ~Pipe();

	virtual void bonk();

private:
	virtual void doSomethingUnique();
};

/*****Peach Class*****/
class Peach : public Actor
{
public:

	Peach(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);
	virtual ~Peach();

	//Peach has health
	void setHP(int hp);
	int getHP();
	void decHP();

	//Peach can jump
	int getJumpPower();
	void setJumpPower(int remaining_jump_power);
	void decJumpPower();

	virtual void bonk();

private:
	virtual void doSomethingUnique();
	int m_hp;
	int remaining_jump_power;
};


#endif // ACTOR_H_
