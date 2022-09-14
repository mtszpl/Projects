#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "Weapon.h"

class Creature
{
protected:
	int mHp;
	int mCordX;
	int mBoxX;
	int mCordY;
	int mBoxY;
	int mMovDir;
	bool mAlive = true;

	Weapon mGun;

	ALLEGRO_BITMAP* mSkin;
	ALLEGRO_COLOR mColor;

public:
	Creature(int hp, int xCord, int yCord, char type);
	~Creature();

	void draw();

	virtual void move();
	Bullet* shoot();
	void reload();
	void collisionWithBullet(Bullet& missle);
	void getHurt(int wound);

	int getDir() const;
	int getX() const;
	int getY() const;
	bool getStatus() const;

	Weapon getWeapon() const;
};

