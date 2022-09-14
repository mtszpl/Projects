#include "Creature.h"

Creature::Creature(int hp, int xCord, int yCord, char type)
{
	mHp = hp;
	mCordX = xCord;
	mBoxX = mCordX + 20;
	mCordY = yCord;
	mBoxY = mCordY + 64;
	mMovDir = 0;

	mSkin = NULL;
}

Creature::~Creature()
{
	al_destroy_bitmap(mSkin);
}

void Creature::draw()
{
	if (mSkin == NULL)
	{
		ALLEGRO_COLOR enemCol = al_map_rgb(255, 0, 0);
		al_draw_rectangle(mCordX, mCordY, mBoxX, mBoxY, enemCol, 2.0);
	}
	else
		al_draw_bitmap(mSkin, mCordX, mCordY, NULL);
}

void Creature::collisionWithBullet(Bullet& missle)
{
	if (mAlive == false)
		return;
	int bulletX = missle.getCordX();
	int bulletY = missle.getCordY();
	if (bulletX > mCordX && bulletX < mBoxX && bulletY > mCordY && bulletY < mBoxY)
	{
		getHurt(missle.getDamage());
		missle.setFlyFalse();
	}
}

void Creature::getHurt(int wound)
{
	mHp -= wound;
	if (mHp < 1)
		mAlive = false;
}

void Creature::move()
{

}

void Creature::reload()
{
	mGun.reload();
}

Bullet* Creature::shoot()
{
	return mGun.shoot(mMovDir, mCordX, mCordY);
}

int Creature::getDir() const
{
	return mMovDir;
}

bool Creature::getStatus() const
{
	return mAlive;
}

Weapon Creature::getWeapon() const
{
	return mGun;
}

int Creature::getX() const
{
	return mCordX;
}

int Creature::getY() const
{
	return mCordY;
}