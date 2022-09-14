#pragma once
#include <allegro5/allegro_primitives.h>
#include "classPrototypes.h"

class Bullet
{
private:
	int mDamage;
	int mDir;
	int mVelocity = 20;

	int mCordX;
	int mBoxX;
	int mCordY;
	int mBoxY;
	bool mFly;
	int mMovDisplacement;

	int* mCord = nullptr;
	int* mBox = nullptr;

	ALLEGRO_COLOR mColor;
public:
	Bullet(int dmg, ALLEGRO_COLOR col);
	Bullet();
	~Bullet();

	int shoot(int dir, int xCord, int yCord);
	void letFly();
	void draw();

	void hit(Creature& target);

	int getCordX() const;
	int getCordY() const;
	int getDamage() const;
	bool getFly() const;
	int getMovDisplacement() const;
	int* getCordPointer() const;
	int* getBoxPointer() const;
	void setFlyFalse();

	char isPonting();

	void operator=(Bullet tmp);

#ifdef _DEBUG
	bool fuckYou();
#endif
};

