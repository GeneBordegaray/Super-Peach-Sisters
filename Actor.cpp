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

int Actor::getGoodieType() const
{
	return 0;
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





/*****Goodie Base Class*****/
Goodie::Goodie(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Actor(world, imageID, startX, startY, startDirection, depth, size)
{}
Goodie::~Goodie()
{}






/*****Block*****/
Block::Block(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size, GoodieType g)
	:stationaryActors(world, imageID, startX, startY, startDirection, depth, size)
{
	//does this initialized block currently have a goodie?
	if (g == none)
	{
		m_goodieCount = 0;
		m_goodieType = 0;
	}
	else
	{
		//what type of goodie is in this block
		switch (g)
		{
		case(mushroom):
			m_goodieType = 1;
			break;

		case(flower):
			m_goodieType = 2;
			break;

		case(star):
			m_goodieType = 3;
			break;

		default:
			break;
		}

		//make sure we know a goodie is in here
		m_goodieCount = 1;
	}


}
Block::~Block()
{}

//returns the type of goodie in the block
int Block::getGoodieType() const
{
	return m_goodieType;
}

//event when block is bonked
void Block::bonk()
{
	//if there are no goodies in this block then just simple bonk
	if (m_goodieCount <= 0)
	{
		getWorld()->playSound(SOUND_PLAYER_BONK);
		return;
	}
	//what to do if there currently is a goodie in the block
	else
	{
		getWorld()->playSound(SOUND_POWERUP_APPEARS);
		//mushroom

		if (m_goodieType == 1)
		{
			getWorld()->addGoodie(this);
		}


		//no more goodie in this block
		m_goodieCount--;
	}
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
	//Peach doesn't start wih mushroom
	setHasMushroom(false);
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

//Peach when she has a mushroom power up
void Peach::setHasMushroom(bool mush) 
{
	m_hasMushroom = mush;
}
bool Peach::getHasMushroom() const
{
	return m_hasMushroom;
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

	//set temporary invincibility
	setInvincible(10);

	if (getHasMushroom())
	{
		setHasMushroom(false);
	}


	//is peach still alive
	if (getHP() > 0)
	{
		getWorld()->playSound(SOUND_PLAYER_HURT);
	}
	//if peach dies
	else
	{
		getWorld()->playSound(SOUND_PLAYER_DIE);
		setDead();
	}
}

void Peach::doSomethingUnique()
{
	std::cout << m_hp;
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
				//does peach currently have a mushroom
				if (getHasMushroom())
				{
					remaining_jump_power = 12;
				}
				else
				{
					remaining_jump_power = 8;
				}
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





/*****Mushroom Class*****/
Mushroom::Mushroom(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Goodie(world, imageID, startX, startY, startDirection, depth, size)
{}
Mushroom::~Mushroom()
{}

void Mushroom::doSomethingUnique()
{
	if (!isAlive())
	{
		return;
	}
	//is the mushroom overlapping peach
	if (getWorld()->overlapPeach(this))
	{
		//update peach score
		getWorld()->increaseScore(75);

		//tell peach she has jump power
		getWorld()->grantJumpPower();

		//peach cna take one extra hit when she has power ups
		getWorld()->setPeachHP(2);

		//no longer in the game
		setDead();

		getWorld()->playSound(SOUND_PLAYER_POWERUP);

		return;
	}

	//should the mushroom be falling
	if (getWorld()->canMoveThere(this, getX(), getY() - 1))
	{
		moveTo(getX(), getY() - 2);
	}

	//determine which way the mushroom is facing
	if (getDirection() == left)
	{
		//where the mushroom wants to go
		double destX = getX() - 2;
		double destY = getY();

		//is this valid spot to move
		//if not turn around
		if (!getWorld()->canMoveThere(this, destX, destY))
		{
			reverseActor();
			return;
		}
		//if so then move there
		else
		{
			moveTo(destX, destY);
		}
	}
	//facing right
	else
	{
		//where the mushroom wants to go
		double destX = getX() + 2;
		double destY = getY();

		//is this valid spot to move
		//if not turn around
		if (!getWorld()->canMoveThere(this, destX, destY))
		{
			reverseActor();
			return;
		}
		//if so then move there
		else
		{
			moveTo(destX, destY);
		}
	}
}
