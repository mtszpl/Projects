#include "Bullet.h"
#include "Creature.h"
#include <allegro5/allegro5.h>
#include <iostream>

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define MOVEVALUE 5

Bullet::Bullet(int dmg, ALLEGRO_COLOR col)
{
	mDamage = dmg;
	mCordX = 0;
	mBoxX = 0;
	mCordY = 0;
	mBoxY = 0;
	mDir = 0;
	mMovDisplacement = 0;
	mFly = false;
	mColor = col;
}

Bullet::Bullet() : Bullet::Bullet(0, al_map_rgb(0, 0, 0))
{
}

Bullet::~Bullet()
{

}

int Bullet::shoot(int dir, int xCord, int yCord)
{
	if (dir)
		mDir = dir;
	else
		mDir = LEFT;
	mCordX = xCord + 25;
	mBoxX = mCordX + 10;
	mCordY = yCord + 32;
	mBoxY = mCordY + 10;
	int factor = 1;

	if (mDir == UP || mDir == DOWN)
	{
		mCord = &mCordY;
		mBox = &mBoxY;
	}
	if (mDir == LEFT || mDir == RIGHT)
	{
		mCord = &mCordX;
		mBox = &mBoxX;
	}
	if (mDir == UP || mDir == LEFT)
		factor = -1;
	mFly = true;
	mMovDisplacement = mVelocity * factor;
	return mMovDisplacement;
}

void Bullet::letFly()
{
	if (mCordX < 0 || mCordX > 1280 || mCordY < 0 || mCordY > 708)
	{
		mFly = false;
		return;
	}
	if (mFly == false)
		return;
	*mCord += mMovDisplacement;
	*mBox += mMovDisplacement;
	draw();
}

void Bullet::draw()
{
	al_draw_rectangle(mCordX, mCordY, mBoxX, mBoxY, mColor, 2.0);
}

void Bullet::hit(Creature& target)
{
	if (target.getStatus() == false)
		return;

	int targetX = target.getX();
	int targetY = target.getY();
	if (mCordX > targetX && targetX + 20 < mCordX && targetY < mCordY && targetY + 64 > mCordY)
	{
		target.getHurt(mDamage);
		mFly = false;
	}

	/*
	* 	if (mCordX > targetX)
	{
		std::cerr << "more than x\n";
		if (targetX < mCordX + 20)
		{
			std::cerr << "less than xBox\n" << "y = " << mCordX << "tY = " << target.getY() << " yBox = " << targetY + 64;
			if (targetY > mCordY)
			{
				std::cerr << "more than y\n";
				if (targetY < mCordY + 64)
				{
					std::cerr << "werkin\n";
					target.getHurt(mDamage);
					mFly = false;

				}
			}
		}
	}
	*/
}

char Bullet::isPonting()
{
	if (mCord == &mCordX)
		return 'x';
	else if (mCord == &mCordY)
		return 'y';
	return 'w';
}

int Bullet::getCordX() const
{
	return mCordX;
}

int Bullet::getCordY() const
{
	return mCordY;
}

int Bullet::getDamage() const
{
	return mDamage;
}

bool Bullet::getFly() const
{
	return mFly;
}

int Bullet::getMovDisplacement() const
{
	return mMovDisplacement;
}

int* Bullet::getCordPointer() const
{
	return mCord;
}

int* Bullet::getBoxPointer() const
{
	return mBox;
}

void Bullet::setFlyFalse()
{
	mFly = false;
}

void Bullet::operator=(Bullet tmp)
{
	mCordX = tmp.getCordX();
	mBoxX = mCordX + 10;
	mCordY = tmp.getCordY();
	mBoxY = mCordY + 10;
	mDamage = tmp.getDamage();
	mMovDisplacement = tmp.getMovDisplacement();
	mFly = tmp.getFly();

	if (tmp.isPonting() == 'x')
		mCord = &mCordX;
	else if (tmp.isPonting() == 'y')
		mCord = &mCordY;
	else
		mCord = nullptr;
}
