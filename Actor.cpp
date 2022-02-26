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
	m_hp = 1;
	//peach starts with 3 lives
	setHP(1);
	remaining_jump_power = 0;
	remaining_invincbile = 0;
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

//peach needs to be invincible
void Peach::setInvincible(int num)
{
	remaining_invincbile = num;
}
//what is peach's time elft being invincible?
int Peach::getInvincible()
{
	return remaining_invincbile;
}
//decrease peaches time being invincible
void Peach::decInvincible()
{
	remaining_invincbile--;
}
//chek to see if peach is currently invincible
bool Peach::isInvincible() const
{
	if (remaining_invincbile > 0)
	{
		return true;
	}
	return false;
}


void Peach::bonk()
{
	//Is peach currently invincible?
	if (getInvincible() > 0)
	{
		return;
	}

	//loses a life
	decHP();


	//is peach still alive
	if (getHP() > 0)
	{
		getWorld()->playSound(SOUND_PLAYER_HURT);
	}
	//if peach dies
	else
	{
		setDead();
	}
}

void Peach::doSomethingUnique()
{
	//Is peach currenbtly alive
	if (!isAlive())
	{
		return;
	}

	//Peach currently invincible
	if (isInvincible())
	{
		decInvincible();
	}
	//possibly turn off peach's invincibility 
	if (getInvincible() <= 0)
	{
		setInvincible(0);
	}

	//bonking
	//if another actor is overlapped with peach
	if (getWorld()->overlapPeach())
	{
		getWorld()->bonkOverlappingActor(this);
	}
	//if peach hit head on bottom of block
	else if (getJumpPower() > 0 && !getWorld()->canMoveThere(this, getX(), getY() + 1))
	{
		getWorld()->moveOrBonk(this, getX(), getY() + 1);
	}

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
			if (getWorld()->canMoveThere(this, getX() - 4, getY()))
			{
				moveTo(getX() - 4, getY());
			}
			//if we cant move there is a block or a pipe and we want to bonk it, but can't side bonk when jumping
			else if(getJumpPower() <= 0)
			{
				getWorld()->moveOrBonk(this, getX() - 1, getY());
			}
			break;

			//right
		case KEY_PRESS_RIGHT:
			//set peaches direction prior to actually moving
			setDirection(right);
			//checking that the destination she wants to move to is a valid one
			if (getWorld()->canMoveThere(this, getX() + 4, getY()))
			{
				moveTo(getX() + 4, getY());
			}
			//if we cant move there is a block or a pipe and we want to bonk it, but can's side bonk when jumping
			else if (getJumpPower() <= 0)
			{
				getWorld()->moveOrBonk(this, getX() + 1, getY());
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





/*****Goomba Class*****/
Goomba::Goomba(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:BadGuy(world, imageID, startX, startY, startDirection, depth, size)
{}
Goomba::~Goomba()
{}


void Goomba::bonk()
{

}

void Goomba::doSomethingUnique()
{
	//is the goomba alive
	if (!isAlive())
	{
		return;
	}

	//is goomba currently touching peach
	if (getWorld()->overlapPeach(this))
	{
		//get bonked nerd
		getWorld()->bonkOverlappingPeach(this);
		return;
	}

	//moving
	//get where teh goomba wants to go
	double destinationX;
	if (getDirection() == left)
	{
		destinationX = getX() - 1;
	}
	else
	{
		destinationX = getX() + 1;
	}
	double destinationY = getY();

	//can the goomba goes where it wants? if not turn around
	if (!getWorld()->canMoveThere(this, destinationX, destinationY) || getWorld()->canMoveThere(this, destinationX - 4, destinationY - 1) || getWorld()->canMoveThere(this, destinationX + 4, destinationY - 1))
	{
		reverseActor();
	}
	//check if the path is blocked or empty the way the goomba is going 
	if (getDirection() == left && getWorld()->canMoveThere(this, destinationX, destinationY) && !getWorld()->canMoveThere(this, destinationX-4, destinationY-1))
	{
		moveTo(destinationX, destinationY);
	}
	else if (getDirection() == right && getWorld()->canMoveThere(this, destinationX, destinationY) && !getWorld()->canMoveThere(this, destinationX + 4, destinationY - 1))
	{
		moveTo(destinationX, destinationY);
	}
}
