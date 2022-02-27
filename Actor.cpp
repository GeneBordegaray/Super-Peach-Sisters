#include "Actor.h"
#include "StudentWorld.h"

/*****Base Actor*****/
Actor::Actor(StudentWorld * world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:GraphObject(imageID, startX, startY, startDirection, depth, size)
{
	m_world = world;
	m_alive = true;
}

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

bool Actor::canTakeDamage() const
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

bool Actor::isKoopa() const
{
	return false;
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

//All stationary actors can block movement
bool stationaryActors::canBlock() const
{
	return true;
}

/*****Bad Guy Actor Class*****/
BadGuy::BadGuy(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Actor(world, imageID, startX, startY, startDirection, depth, size)
{}


bool BadGuy::canTakeDamage() const
{
	return true;
}

void BadGuy::doSomething()
{
	if (!isAlive())
	{
		return;
	}
	doSomethingUnique();
	//moving
	//get where teh badguy wants to go
	double destinationX;
	double destinationY = getY();
	if (getDirection() == left)
	{
		destinationX = getX() - 1;
		//can the badguy goes where it wants? if not turn around
		if (!getWorld()->canMoveThere(this, destinationX, destinationY) || getWorld()->canMoveThere(this, destinationX - 7, destinationY - 1))
		{
			reverseActor();
			return;
		}
		moveTo(destinationX, destinationY);
		return;
	}
	else
	{
		destinationX = getX() + 1;
		if (!getWorld()->canMoveThere(this, destinationX, destinationY) || getWorld()->canMoveThere(this, destinationX + 7, destinationY - 1))
		{
			reverseActor();
			return;
		}
		moveTo(destinationX, destinationY);
		return;
	}
	return;
}


void BadGuy::bonk()
{
	//if not peach dont do anything
	if (!getWorld()->overlapPeach(this))
	{
		return;
	}
	//if it is peach
	else
	{
		//check if peach has star power
		if (getWorld()->getStarPower())
		{
			getWorld()->playSound(SOUND_PLAYER_KICK);

			//increase score
			getWorld()->increaseScore(100);

			//gommab dead
			setDead();

			//only if koopa
			if (isKoopa())
			{
				getWorld()->deleteActorAddShell();
			}
		}
	}
}

void BadGuy::sufferDamage()
{
	//increase players score
	getWorld()->increaseScore(100);

	//kill the goomba
	setDead();

	//only if koopa
	if (isKoopa())
	{
		getWorld()->deleteActorAddShell();
	}
}



/*****Goodie Base Class*****/
Goodie::Goodie(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Actor(world, imageID, startX, startY, startDirection, depth, size)
{}

void Goodie::doSomething()
{
	if (!isAlive())
	{
		return;
	}
	doSomethingUnique();
	//should the goodie be falling
	if (getWorld()->canMoveThere(this, getX(), getY() - 1))
	{
		moveTo(getX(), getY() - 2);
	}

	//determine which way the goodie is facing
	if (getDirection() == left)
	{
		//where the goodie wants to go
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
		//where the goodie wants to go
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

/*****Projectile Base Class*****/
Projectile::Projectile(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Actor(world, imageID, startX, startY, startDirection, depth, size)
{}

void Projectile::doSomething()
{
	if (!isAlive())
	{
		return;
	}

	doSomethingUnique();

	//should the fireball be falling
	if (getWorld()->canMoveThere(this, getX(), getY() - 2))
	{
		moveTo(getX(), getY() - 2);
	}

	//which way is the fireball facing
	if (getDirection() == left)
	{
		//find where the fireball wants to go
		double destX = getX() - 2;
		double destY = getY();

		//is this a valid position
		//if not then die
		if (!getWorld()->canMoveThere(this, destX, destY))
		{
			setDead();
			return;
		}
		//if it is then go there
		else
		{
			moveTo(destX, destY);
		}
	}
	else
	{
		//find where the fireball wants to go
		double destX = getX() + 2;
		double destY = getY();

		//is this a valid position
		//if not then die
		if (!getWorld()->canMoveThere(this, destX, destY))
		{
			setDead();
			return;
		}
		//if it is then go there
		else
		{
			moveTo(destX, destY);
		}
	}
}





/*****Block*****/
Block::Block(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size, int goodieType)
	:stationaryActors(world, imageID, startX, startY, startDirection, depth, size)
{
	//does this initialized block currently have a goodie?
	if (goodieType == 0)
	{
		m_goodieCount = 0;
		m_goodieType = 0;
	}
	else
	{
		m_goodieType = goodieType;
		//make sure we know a goodie is in here
		m_goodieCount = 1;
	}


}

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

		//Add the goodie to the world
		switch (m_goodieType)
		{
		case 1:
			getWorld()->addActor(new Mushroom(getWorld(), IID_MUSHROOM, int(getX()), int(getY() + 8), 0, 1, 1.0));
			break;

		case 2:
			getWorld()->addActor(new Flower(getWorld(), IID_FLOWER, int(getX()), int(getY() + 8), 0, 1, 1.0));
			break;

		case 3:
			getWorld()->addActor(new Star(getWorld(), IID_STAR, int(getX()), int(getY() + 8), 0, 1, 1.0));
			break;

		default:
			break;
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
	//Peach doesn't start with flower
	setHasFlower(false);
	//peach doesn't start with star
	setHasStar(false);
	remaining_jump_power = 0;
	remaining_invincbile = 0;
	remaining_recharge = 0;
	remaining_star = 0;
}

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

//Peach needs to recharge after fireball shots
void Peach::setRecharge(int num)
{
	remaining_recharge = num;
}
int Peach::getRecharge()
{
	return remaining_recharge;
}
void Peach::decRecharge()
{
	remaining_recharge--;
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

//peach with a flower poewr up
void Peach::setHasFlower(bool flower)
{
	m_hasFlower = flower;
}
bool Peach::getHasFlower() const
{
	return m_hasFlower;
}

//peach with a star
void Peach::setHasStar(bool star)
{
	m_hasStar = star;
}
bool Peach::getHasStar() const
{
	return m_hasStar;
}
void Peach::setTimeStar(int num)
{
	remaining_star = num;
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
	setInvincible(remaining_invincbile+10);

	//turn off powers
	if (getHasMushroom())
	{
		setHasMushroom(false);
	}
	if (getHasFlower())
	{
		setHasFlower(false);
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
	//Is peach currenbtly alive
	if (!isAlive())
	{
		return;
	}

	//if star power time is up no more star power
	if (remaining_star <= 0)
	{
		setHasStar(false);
	}
	//if has star power decrease time left
	if (getHasStar())
	{
		remaining_star--;
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

	//Recharge
	if (getRecharge() > 0)
	{
		decRecharge();
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

		case KEY_PRESS_SPACE:
			//chekc if peach currently has shooting power
			if (!getHasFlower())
			{
				return;
			}
			//what is peach is still recharging from lat shot
			if (getRecharge() > 0)
			{
				return;
			}
			//if does have shooting power
			getWorld()->playSound(SOUND_PLAYER_FIRE);
			
			//set the recharge
			setRecharge(8);

			//which way should fireball go
			if (getDirection() == left)
			{
				getWorld()->addActor(new PeachFireball(getWorld(), IID_PEACH_FIRE, int(getX() - 4), int(getY()), getDirection(), 1,  1.0));
			}
			else
			{
				getWorld()->addActor(new PeachFireball(getWorld(), IID_PEACH_FIRE, int(getX() + 4), int(getY()), getDirection(), 1, 1.0));
			}

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
}

/*****Koopa Class*****/
Koopa::Koopa(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:BadGuy(world, imageID, startX, startY, startDirection, depth, size)
{}

//this is a koopa
bool Koopa::isKoopa() const
{
	return true;
}

//koopas do stuff
void Koopa::doSomethingUnique()
{
	//make sure the koopa is alive
	if (!isAlive())
	{
		return;
	}

	//is koopa overlapping peach
	if (getWorld()->overlapPeach(this))
	{
		//get bonked nerd
		getWorld()->bonkOverlappingPeach(this);
		return;
	}
}


/*****Piranha Class*****/
Piranha::Piranha(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Actor(world, imageID, startX, startY, startDirection, depth, size)
{
	//starts with no delay
	fire_delay = 0;
}

bool Piranha::canTakeDamage() const
{
	return true;
}

//piranha do things differently then other bad guys
void Piranha::doSomehting()
{
	if (!isAlive())
	{
		return;
	}
	doSomethingUnique();
}

void Piranha::sufferDamage()
{
	//Increase score by 100
	getWorld()->increaseScore(100);

	//koopa is now dead
	setDead();

	//add a shell into the game while deleteing the koopa so no over lap
	getWorld()->deleteActorAddShell();
}

//get bonked nerd
void Piranha::bonk()
{
	//if not peach dont do anything
	if (!getWorld()->overlapPeach(this))
	{
		return;
	}
	//if it is peach
	else
	{
		//check if peach has star power
		if (getWorld()->getStarPower())
		{
			getWorld()->playSound(SOUND_PLAYER_KICK);

			//increase score
			getWorld()->increaseScore(100);

			//gommab dead
			setDead();

			//delete teh koopa and add shell
			getWorld()->deleteActorAddShell();
		}
	}
}

void Piranha::doSomethingUnique()
{
	//make sure it is alive still
	if (!isAlive())
	{
		return;
	}
	increaseAnimationNumber();
	//is the piranha touching peach
	if (getWorld()->overlapPeach(this))
	{
		//bonk that nerd
		getWorld()->bonkOverlappingPeach(this);
		return;
	}
	//are they on the same y
	if (abs(getWorld()->peachY() - this->getY()) > 1.5 * SPRITE_HEIGHT)
	{
		return;
	}
	//face the right way
	if (getWorld()->peachX() > this->getX())
	{
		setDirection(right);
	}
	else
	{
		setDirection(left);
	}
	//does the piranha have firing delay
	if (fire_delay > 0)
	{
		//just decrese it and do nothing else
		fire_delay--;
		return;
	}
	//is peach close enough to shoot
	if (abs(getWorld()->peachX() - int(this->getX())) < 8*SPRITE_HEIGHT)
	{
		//do all this stuff
		getWorld()->addActor(new PiranhaFireball(getWorld(), IID_PIRANHA_FIRE, int(getX()), int(getY()), getDirection(), 1, 1.0));
		getWorld()->playSound(SOUND_PIRANHA_FIRE);
		fire_delay = 40;
		return;
	}
}

/*****Mushroom Class*****/
Mushroom::Mushroom(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Goodie(world, imageID, startX, startY, startDirection, depth, size)
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
}




/*****Flower Class*****/
Flower::Flower(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Goodie(world, imageID, startX, startY, startDirection, depth, size)
{}

void Flower::doSomethingUnique()
{
	if (!isAlive())
	{
		return;
	}
	//is the flower overlapping peach
	if (getWorld()->overlapPeach(this))
	{
		//update peach score
		getWorld()->increaseScore(50);

		//tell peach she has shooter power
		getWorld()->grantShootingPower();

		//peach cna take one extra hit when she has power ups
		getWorld()->setPeachHP(2);

		//no longer in the game
		setDead();

		getWorld()->playSound(SOUND_PLAYER_POWERUP);

		return;
	}
}

/*****Star Goodie*****/
Star::Star(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Goodie(world, imageID, startX, startY, startDirection, depth, size)
{}

void Star::doSomethingUnique()
{
	if (!isAlive())
	{
		return;
	}
	//is the star overlapping peach
	if (getWorld()->overlapPeach(this))
	{
		//update peach score
		getWorld()->increaseScore(100);

		//tell peach she has invincibility power
		getWorld()->grantInvinciblePower();

		//no longer in the game
		setDead();

		getWorld()->playSound(SOUND_PLAYER_POWERUP);

		return;
	}
}

/*****Peach Fireball*****/
PeachFireball::PeachFireball(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Projectile(world, imageID, startX, startY, startDirection, depth, size)
{}

void PeachFireball::doSomethingUnique()
{
	//is the peach fireball touching something that should be damaged
	if (getWorld()->damageOverlappingActor(this))
	{
		setDead();
		return;
	}
}

/*****Shell Class *****/
Shell::Shell(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Projectile(world, imageID, startX, startY, startDirection, depth, size)
{}

void Shell::doSomethingUnique()
{
	if (getWorld()->damageOverlappingActor(this))
	{
		//shell dies after hitting actor
		setDead();
		return;
	}
}

/*****Piranha Fireball class******/
PiranhaFireball::PiranhaFireball(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Projectile(world, imageID, startX, startY, startDirection, depth, size)
{}

void PiranhaFireball::doSomethingUnique()
{
	if (getWorld()->overlapPeach(this))
	{
		//piranha fireball dies after hitting peach
		getWorld()->bonkOverlappingPeach(this);
		setDead();
		return;
	}
}

/*****Flag Ender Class*****/
Flag::Flag(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Actor(world, imageID, startX, startY, startDirection, depth, size)
{}

void Flag::doSomethingUnique()
{
	//make sure it is alive
	if (!isAlive())
	{
		return;
	}

	//is it overlapping with peach
	//if so then...
	if (getWorld()->overlapPeach(this))
	{
		//increase the score
		getWorld()->increaseScore(1000);

		//not alive anymore
		setDead();

		getWorld()->playSound(SOUND_FINISHED_LEVEL);

		//let the world know that the level is complete
		getWorld()->endLevel(true);
	}
}


/*****Mario Ender Class*****/
Mario::Mario(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth, double size)
	:Actor(world, imageID, startX, startY, startDirection, depth, size)
{}

void Mario::doSomethingUnique()
{
	//make sure it is alive
	if (!isAlive())
	{
		return;
	}

	//is it overlapping with peach
	//if so then...
	if (getWorld()->overlapPeach(this))
	{
		//increase the score
		getWorld()->increaseScore(1000);

		//not alive anymore
		setDead();

		getWorld()->playSound(SOUND_FINISHED_LEVEL);

		//end game
		getWorld()->endLevel(true);
		getWorld()->endGame(true);
	}
}
