#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

/*****Base Actor*****/
Actor::Actor(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:GraphObject(imageID, startX, startY, startDirection, depth, size)
{}
Actor::~Actor()
{}

StudentWorld* Actor::getWorld() const
{
	return m_world;
}

/*****Block*****/
Block::Block(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Actor(world, imageID, startX, startY, startDirection, depth, size)
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
	bool alive = isAlive();
	if (alive)
	{

		int keyPress;
		if (getWorld()->getKey(keyPress))
		{

			switch (keyPress)
			{

			case KEY_PRESS_LEFT:
				setDirection(left);
				moveTo(getX() - 4, getY());
				break;

			case KEY_PRESS_RIGHT:
				setDirection(right);
				moveTo(getX() + 4, getY());
				break;
			}
		}
	}
	return;
}
