#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

/*****Base Actor*****/
Actor::Actor(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:GraphObject(imageID, startX, startY, startDirection, depth, size)
{
	m_world = world;
}
Actor::~Actor()
{}

bool Actor::canBlock()
{
	return false;
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


/*****Block*****/
Block::Block(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:stationaryActors(world, imageID, startX, startY, startDirection, depth, size)
{}
Block::~Block()
{}

void Block::doSomething()
{}


/*****Peach*****/
Peach::Peach(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Actor(world, imageID, startX, startY, startDirection, depth, size)
{
	m_hp = 3;
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

void Peach::doSomething()
{
	
	int keyPress;
	if (getWorld()->getKey(keyPress))
	{

		switch (keyPress)
		{
		case KEY_PRESS_LEFT:
			setDirection(left);
			if (getWorld()->isBlockedPath(this) == false)
			{
				moveTo(getX() - 4, getY());
			}
			break;

		case KEY_PRESS_RIGHT:
			setDirection(right);
			if (getWorld()->isBlockedPath(this) == false)
			{
				moveTo(getX() + 4, getY());
			}
			break;
			/*
		case KEY_PRESS_UP:
			if (getWorld()->isBlockedPath(this) == false)
			{
				moveTo(getX(), getY() + 4);
			}
			break;
			*/
		default:
			break;
		}
	
	}
return;
}
