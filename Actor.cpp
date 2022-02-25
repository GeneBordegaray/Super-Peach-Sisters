#include "Actor.h"
#include "StudentWorld.h"

/*****Base Actor*****/
Actor::Actor(StudentWorld * world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:GraphObject(imageID, startX, startY, startDirection, depth, size)
{
	m_world = world;
	m_alive = true;
}
Actor::~Actor()
{}


bool Actor::canBlock() //Can all pl;ayers block
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




/*****Bad Guy Actor Class*****/
BadGuy::BadGuy(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Actor(world, imageID, startX, startY, startDirection, depth, size)
{}
BadGuy::~BadGuy()
{}

bool BadGuy::doesDamage()
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
	m_hp = 3;
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

	//Jumping
	if (remaining_jump_power > 0)
	{
		//where does peach want to go?
		double destinationX = getX();
		double destinationY = getY() + 4;

		//chek if blocked path
		if (!getWorld()->canMoveThere(this, destinationX, destinationY))
		{
			remaining_jump_power = 0;
		}
		else
		{
			moveTo(destinationX, destinationY);
			decJumpPower();
		}
	}
	//if not jumpping falling?
	else
	{
		//check if something is prohibiting peach from falling
		if (getWorld()->canMoveThere(this, getX(), getY() - 1) && getWorld()->canMoveThere(this, getX(), getY() - 3))
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
			//left
		case KEY_PRESS_LEFT:
			//set peaches direction prior to actually moving
			setDirection(left);
			//checking that the destination she wants to move to is a valid one
			if (getWorld()->canMoveThere(this, getX() - 4, getY()) && getWorld()->canMoveThere(this, getX() - 4, getY() + SPRITE_HEIGHT - 1))
			{
				moveTo(getX() - 4, getY());
			}
			break;

			//right
		case KEY_PRESS_RIGHT:
			//set peaches direction prior to actually moving
			setDirection(right);
			//checking that the destination she wants to move to is a valid one
			if (getWorld()->canMoveThere(this, getX() + 4, getY()) && getWorld()->canMoveThere(this, getX() + 4, getY() + SPRITE_HEIGHT - 1))
			{
				moveTo(getX() + 4, getY());
			}
			break;

			//up
		case KEY_PRESS_UP:
			//check if a block or pipe is currently under peach
			if (!getWorld()->canMoveThere(this, getX(), getY() - 1))
			{
				remaining_jump_power = 8;
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

