#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

/*****Base Actor*****/
Actor::Actor(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:GraphObject(imageID, startX, startY, startDirection, depth, size)
{
	m_world = world;
	m_alive = true;
}
Actor::~Actor()
{}

bool Actor::canBlock()
{
	return false;
}
bool Actor::doesDamage()
{
	return false;
}
bool Actor::isAlive()
{
	return m_alive;
}

StudentWorld* Actor::getWorld() const
{
	return m_world;
}

/*****Sationary Actors Base Class*****/
stationaryActors::stationaryActors(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Actor(world, imageID, startX, startY, startDirection, depth, size)
{}
stationaryActors::~stationaryActors()
{}

bool stationaryActors::canBlock()
{
	return true;
}

/*****Bad Guy Base Class*****/
badGuy::badGuy(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Actor(world, imageID, startX, startY, startDirection, depth, size)
{}
badGuy::~badGuy()
{}

bool badGuy::doesDamage()
{
	return true;
}

/*****Block*****/
Block::Block(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:stationaryActors(world, imageID, startX, startY, startDirection, depth, size)
{}
Block::~Block()
{}

void Block::doSomething()
{}
void Block::bonk()
{
	getWorld()->playSound(SOUND_PLAYER_BONK);
}


/*****Pipes*****/
Pipe::Pipe(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:stationaryActors(world, imageID, startX, startY, startDirection, depth, size)
{}
Pipe::~Pipe()
{}

void Pipe::doSomething()
{}
void Pipe::bonk()
{
	return;
}


/*****Peach*****/
Peach::Peach(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Actor(world, imageID, startX, startY, startDirection, depth, size)
{
	m_hp = 1;
	remaining_jump_power = 0;
}
Peach::~Peach()
{}

bool Peach::isAlive()
{
	if (m_hp > 0)
	{
		return true;
	}
	return false;
}
void Peach::setHP(int hp)
{
	m_hp = hp;
}
int Peach::getHP()
{
	return m_hp;
}
void Peach::decHP()
{
	m_hp--;
}


int Peach::getJumpPower()
{
	return remaining_jump_power;
}
void Peach::setJumpPower(int num)
{
	remaining_jump_power = num;
}
void Peach::decJumpPower()
{
	remaining_jump_power--;
}

void Peach::doSomething()
{
	if (isAlive() == false)
	{
		return;
	}

	if (getWorld()->overObject(this) == true)
	{
		bonk();
	}

	bool directionCheck[4];

	if (getJumpPower() > 0)
	{
		if (getWorld()->isBlockedPath(this, directionCheck)[0] == true)
		{
			setJumpPower(0);
		}
		else
		{
			moveTo(getX(), getY() + 4);
			decJumpPower();
		}
	}
	else
	{
		if (getWorld()->isBlockedPath(this, directionCheck)[1] == false)
		{
			moveTo(getX(), getY() - 4);
		}
	}


	//key inputs
	int keyPress;
	if (getWorld()->getKey(keyPress))
	{
		
		switch (keyPress)
		{
		//west
		case KEY_PRESS_LEFT:
			setDirection(left);
			if (getWorld()->isBlockedPath(this, directionCheck)[3] == false) //blocked path doesn't allow you to move but can change directions
			{
				moveTo(getX() - 4, getY());
			}
			break;

		//east
		case KEY_PRESS_RIGHT:
			setDirection(right);
			if (getWorld()->isBlockedPath(this, directionCheck)[2] == false)//blocked path doesn't allow you to move but can change directions
			{
				moveTo(getX() + 4, getY());
			}
			break;
			
		//north
		case KEY_PRESS_UP:
			if (getWorld()->isBlockedPath(this, directionCheck)[1] == true)//blocked path doesn't allow you to move but can change directions
			{
				setJumpPower(8);
			}
			getWorld()->playSound(SOUND_PLAYER_JUMP);
			break;
		
		}
	
	}
return;
}
void Peach::bonk()
{
	return;
}


/*****Goomba Class*****/
Goomba::Goomba(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	: badGuy(world, imageID, startX, startY, startDirection, depth, size)
{}
Goomba::~Goomba()
{}

void Goomba::doSomething()
{
	//std::cout << "hey";
	bool directionCheck[4];

	//west
	if (getWorld()->isBlockedPath(this, directionCheck)[3] == true) //blocked path doesn't allow you to move but can change directions
	{
		setDirection(0);
	}

	//east
	if (getWorld()->isBlockedPath(this, directionCheck)[2] == true)//blocked path doesn't allow you to move but can change directions
	{
		setDirection(180);
	}

	if (getDirection() == 0) //check which way goomba is facing
	{
		moveTo(getX() + 1, getY());
	}
	else //check which way the goomba is moving
	{
		moveTo(getX() - 1, getY());
	}
}
void Goomba::bonk()
{}
