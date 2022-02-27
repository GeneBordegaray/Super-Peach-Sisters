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

	//can this character be damaged
	virtual bool canTakeDamage() const;

	virtual int getGoodieType() const;

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


private:

};




/*****Goodie Base Class*****/
class Goodie : public Actor
{
public:
	Goodie(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);
	virtual ~Goodie();

private:

};




/*****Projectile Base Class*****/
class Projectile : public Actor
{
public:
	Projectile(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);
	virtual ~Projectile();

private:

};




/*****Block*****/
class Block : public stationaryActors
{
public:
	//blocks can have different goodies in them
	//0 is none, 1 is mushroom, 2 is flower, 3 is star
	int goodieArr[4] = { 0, 1, 2, 3 };


	Block(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size, int goodieType);
	virtual ~Block();

	//what type of goodie is in the block
	virtual int getGoodieType() const;

	virtual void bonk();

private:
	int m_goodieCount;
	//1 is mushroom, 2 is flower, 3 is start, 0 is nothing
	int m_goodieType;
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
	void setJumpPower(int num);
	void decJumpPower();

	//peach needs to be invincible for some periods of time
	void setInvincible(int remaining_invincible);
	int getInvincible();
	void decInvincible();
	bool isInvincible() const;

	//peach needs to reacharge fire ball shots for some periods of time
	void setRecharge(int num);
	int getRecharge();
	void decRecharge();

	//peach with a mushroom power up
	void setHasMushroom(bool mush);
	bool getHasMushroom() const;

	//peach with a flower poewr up
	void setHasFlower(bool flower);
	bool getHasFlower() const;

	virtual void bonk();

private:
	virtual void doSomethingUnique();
	int m_hp;
	bool m_hasMushroom;
	bool m_hasFlower;
	int remaining_jump_power;
	int remaining_invincbile;
	int remaining_recharge;
};


/*****Goomba Class*****/
class Goomba : public BadGuy
{
public:
	Goomba(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);
	virtual ~Goomba();

	//goombas bonk
	virtual void bonk();

private:
	virtual void doSomethingUnique();
};



/*****Mushroom Class*****/
class Mushroom : public Goodie
{
public:
	Mushroom(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);
	virtual ~Mushroom();

private:
	virtual void doSomethingUnique();
};


/*****Flower Class*****/
class Flower : public Goodie
{
public:
	Flower(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);
	virtual ~Flower();

private:
	virtual void doSomethingUnique();

};



/*****Peach FireBall*****/
class PeachFireball : public Projectile
{
public:
	PeachFireball(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);
	virtual ~PeachFireball();

private:
	virtual void doSomethingUnique();
};


#endif // ACTOR_H_
