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

	//what to do each tick
	virtual void doSomething();
	virtual void doSomethingUnique() = 0;
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

	//is this a koopa
	virtual bool isKoopa() const;

	//turn the character around
	void reverseActor();

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

	virtual bool canBlock() const;
};


/*****Bad Guy Actor Class*****/
class BadGuy : public Actor
{
public:
	BadGuy(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);

	//all bad guys can take damage
	virtual bool canTakeDamage() const;

	//some bad guys do similar things
	virtual void doSomething();

	//bonk
	virtual void bonk();

	//suffer damage
	virtual void sufferDamage();

private:

};

/*****Goodie Base Class*****/
class Goodie : public Actor
{
public:
	Goodie(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);

	virtual void doSomething();

private:

};

/*****Projectile Base Class*****/
class Projectile : public Actor
{
public:
	Projectile(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);

	virtual void doSomething();

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

	virtual void bonk();

private:
	virtual void doSomethingUnique();
};

/*****Peach Class*****/
class Peach : public Actor
{
public:

	Peach(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);

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

	//peach with star power up
	void setHasStar(bool star);
	bool getHasStar() const;
	void setTimeStar(int num);

	virtual void bonk();

private:
	virtual void doSomethingUnique();
	int m_hp;
	bool m_hasMushroom;
	bool m_hasFlower;
	bool m_hasStar;
	int remaining_jump_power;
	int remaining_invincbile;
	int remaining_recharge;
	int remaining_star;
};


/*****Goomba Class*****/
class Goomba : public BadGuy
{
public:
	Goomba(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);


private:
	virtual void doSomethingUnique();
};



/*****Koopa Class*****/
class Koopa : public BadGuy
{
public:
	Koopa(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);

	//Make sure we know this is a koopa
	virtual bool isKoopa() const;

private:
	virtual void doSomethingUnique();
};


/*****Piranha Class*****/
class Piranha : public Actor
{
public:
	Piranha(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);

	//piranha can take damage
	virtual bool canTakeDamage() const;

	//piranhas arent like other bad guys, they dont move, so they need their own do soemthing
	virtual void doSomehting();

	//what happpens when a piranha suffers damage
	virtual void sufferDamage();

	//what does a [iranha do when bonked
	virtual void bonk();

private:
	virtual void doSomethingUnique();

	int fire_delay;
};


/*****Mushroom Class*****/
class Mushroom : public Goodie
{
public:
	Mushroom(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);

private:
	virtual void doSomethingUnique();
};


/*****Flower Class*****/
class Flower : public Goodie
{
public:
	Flower(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);

private:
	virtual void doSomethingUnique();

};


/*****Star Class*****/
class Star : public Goodie
{
public:
	Star(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);

private:
	virtual void doSomethingUnique();
};


/*****Peach FireBall*****/
class PeachFireball : public Projectile
{
public:
	PeachFireball(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);

private:
	virtual void doSomethingUnique();
};

/*****Shell Class*****/
class Shell : public Projectile
{
public:
	Shell(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);

private:
	virtual void doSomethingUnique();
};


/*****Piranha Fireball*****/
class PiranhaFireball : public Projectile
{
public:
	PiranhaFireball(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);

private:
	virtual void doSomethingUnique();
};

/******Level Ender Class*****/
class Flag : public Actor
{
public:
	Flag(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);

private:
	virtual void doSomethingUnique();
};

/*****Mario Ender Class*****/
class Mario : public Actor
{
public:
	Mario(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size);

private:
	virtual void doSomethingUnique();
};

#endif // ACTOR_H_