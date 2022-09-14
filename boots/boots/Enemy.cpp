#include "Enemy.h"
#include "funcs.h"
#include <stdio.h>
#include <cstdlib>

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define MOVEVALUE 5

Enemy::Enemy(int hp, int xCord, int yCord, char type) : Creature(hp, xCord, yCord, type)
{
	mColor = al_map_rgb(255, 0, 0);
	Weapon tmp("Webley Revolver", mColor, 5, 24, 6, 1, false);
	mGun = tmp;
	mMovSpeed = MOVEVALUE;
}

void Enemy::draw()
{
	if (mAlive == false)
		return;
	if (mSkin == NULL)
		al_draw_rectangle(mCordX, mCordY, mBoxX + 20, mBoxY + 20, mColor, 2.0);
	else
		al_draw_bitmap(mSkin, mCordX, mCordY, NULL);
}

//TODO
void Enemy::setMoveDir()
{
	if (!mGotGoal)
		setGoal();
	if (mGoalPostX == mCordX && mGoalPostY == mCordY)
	{
		mGotGoal = false;
		setGoal();
	}
	if (10 + mGoalPostX > mCordX && mGoalPostX > mCordX - 10)
		mMovDir = RIGHT;
	else if (mGoalPostX - 10 < mCordX && mGoalPostX < mCordX + 10)
		mMovDir = LEFT;
	else if (mGoalPostY > mCordY)
		mMovDir = UP;
	else if (mGoalPostY < mCordY)
		mMovDir = DOWN;

	switch (mMovDir)
	{
	case UP:
		mCordY -= (mMovSpeed);
		mBoxY -= (mMovSpeed);
		break;
	case DOWN:
		mCordY += (mMovSpeed);
		mBoxY += (mMovSpeed);
		break;
	case LEFT:
		mCordX -= (mMovSpeed);
		mBoxX -= (mMovSpeed);
		break;
	case RIGHT:
		mCordX += (mMovSpeed);
		mBoxX += (mMovSpeed);
		break;
	}
}

void Enemy::move(int dir)
{
	if (dir == UP && mCordY <= 0)
		return;
	if (dir == DOWN && mBoxY >= 708)
		return;
	if (dir == LEFT && mCordX <= -12)
		return;
	if (dir == RIGHT && mBoxX >= 1251)
		return;
}

void Enemy::monitor(const Character& player)
{
	if (detect(player))
		face(player);
}

bool Enemy::detect(const Character& player)
{
	if (calculateDistance(*this, player) < mViewRange)
		mIsClose = true;
	else
		mIsClose = false;
	return mIsClose;
}

bool Enemy::face(const Character& player)
{
	if (mIsClose == false)
	{
		mISeeYou = false;
		return mISeeYou;
	}
	int x = player.getX() + 5;
	int xBox = x + 20;
	int y = player.getY() + 10;
	int yBox = y + 64;
	if (player.getX() > mCordX && y < mCordY && mCordY < yBox)
		mMovDir = RIGHT;
	else if (player.getX() < mCordX && y < mCordY && mCordY < yBox)
		mMovDir = LEFT;
	else if (player.getY() < mCordY && x < mCordX && mCordX < xBox)
		mMovDir = UP;
	else if (player.getY() > mCordY && x < mCordX && mCordX < xBox)
		mMovDir = DOWN;
	else
	{
		mISeeYou = false;
		return false;
	}
	mISeeYou = true;
	follow(player);
	return mISeeYou;
}

Bullet* Enemy::attack(const Character& player)
{
	if (mISeeYou == true)
		return shoot();
	else
		return nullptr;
}

//TODO
void Enemy::follow(const Character& player)
{
	if (mISeeYou == false)
		return;
	else
		setGoal(player);
}

void Enemy::setGoal()
{
	if (mGotGoal)
		return; //TODO
	mGoalPostX = rand() % 1280;
	mGoalPostY = rand() % 708;
	mGotGoal = true;
}

void Enemy::setGoal(const Character& player)
{
	mGoalPostX = player.getX();
	mGoalPostY = player.getY();
	mGotGoal = true;
}

bool Enemy::getSight() const
{
	return mISeeYou;
}