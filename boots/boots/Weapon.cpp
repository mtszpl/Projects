#include "Weapon.h"

Weapon::Weapon()
{
	mName = "";
	mDamage = 0;
	mAmmoCount = 0;
	mMag = 0;
	mRoF = 0;
	mIsAuto = false;
}

Weapon::Weapon(std::string name, ALLEGRO_COLOR col, int dmg, int ammoCount, int magazine, int rateOfFire, bool isAuto)
{
	mName = name;
	mBulletCol = col;
	mDamage = dmg;
	mAmmoCount = ammoCount;
	mMagSize = magazine;
	mMag = magazine;
	mRoF = rateOfFire;
	mIsAuto = isAuto;
	for (int i = 0; i < mMagSize; i++)
	{
		Bullet ammo(mDamage, col);
		mMagState.push_back(ammo);
	}
}

Bullet* Weapon::shoot(int dir, int xCord, int yCord)
{
	if (mMag < 1 || mMagState.size() < 1)
		return 0;
	Bullet *shot = new Bullet(mMagState[mMag - 1]);
	mMagState.pop_back();
	mMag--;
	shot->shoot(dir, xCord, yCord);
	return shot;
}

void Weapon::reload()
{
	if (mAmmoCount < 1)
		return;
	int lacking = mMagSize - mMag;
	if (mAmmoCount < lacking)
		lacking = mAmmoCount;
	mMag = mMagSize;
	mAmmoCount -= lacking;
	for (int i = 0; i < lacking; i++)
	{
		Bullet ammo(mDamage, mBulletCol);
		mMagState.push_back(ammo);
	}
}

bool Weapon::isAuto()
{
	return mIsAuto;
}

bool Weapon::isFullMag()
{
	if (mMag == 0)
		return false;
	else
		return true;
}