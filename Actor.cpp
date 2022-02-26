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

void Actor::doSomething()
{
	if (m_alive)
	{
		doSomethingUnique();
	}
}

void Actor::bonk()
{}

bool Actor::canBlock() const 
{
	return false;
}

void Actor::sufferDamage() 
{}

bool Actor::isAlive() const
{
	return m_alive;
}

void Actor::setDead()
{
	m_alive = false;
}

void Actor::reverseActor()
{
	int curDirec = getDirection();
	if (curDirec == left)
	{
		setDirection(right);
	}
	else
	{
		setDirection(left);
	}
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

//All stationary actors can block movement
bool stationaryActors::canBlock() const
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

//event when block is bonked
void Block::bonk()
{
	getWorld()->playSound(SOUND_PLAYER_BONK);
}

//blocks dont do much
void Block::doSomethingUnique()
{}






/*****Pipes*****/
Pipe::Pipe(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:stationaryActors(world, imageID, startX, startY, startDirection, depth, size)
{}
Pipe::~Pipe()
{}

//pipes dont do any thing when bonked
void Pipe::bonk()
{}

//pipes are lame and don't do things
void Pipe::doSomethingUnique()
{}






/*****Peach*****/
Peach::Peach(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Actor(world, imageID, startX, startY, startDirection, depth, size)
{
	m_hp = 3;
	//peach starts with 3 lives
	setHP(3);
	remaining_jump_power = 0;
}
Peach::~Peach()
{}

//set peaches hp
void Peach::setHP(int hp)
{
	m_hp = hp;
}
//what is peaches current hp
int Peach::getHP()
{
	return m_hp;
}
//decrease peaches hp
void Peach::decHP()
{
	m_hp--;
}

//what is peaches current jump power
int Peach::getJumpPower()
{
	return remaining_jump_power;
}
//update peaches jump power
void Peach::setJumpPower(int num)
{
	remaining_jump_power = num;
}
//decrease peaches jump power
void Peach::decJumpPower()
{
	remaining_jump_power--;
}

void Peach::bonk()
{
	return;
}

void Peach::doSomethingUnique()
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
				getWorld()->playSound(SOUND_PLAYER_JUMP);
			}
			break;

		default:
			break;
		}

	}
	return;
}
