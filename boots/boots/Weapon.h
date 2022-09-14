#pragma once
#include <string>
#include <vector>
#include "Bullet.h"

class Weapon
{
private:
	std::string mName;
	int mDamage;
	int mAmmoCount;
	int mMagSize;
	int mMag;
	std::vector<Bullet> mMagState;
	int mRoF;
	bool mIsAuto;
	ALLEGRO_COLOR mBulletCol;

public:
	Weapon();
	Weapon(std::string name, ALLEGRO_COLOR bulletCol, int dmg, int ammoCount, int magazine, int rateOfFire, bool isAuto);

	Bullet* shoot(int dir, int xCord, int yCord);
	void reload();

	bool isAuto();
	bool isFullMag();
	//Bullet getBullet();
};

