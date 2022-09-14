#include "Character.h"
#include <stdio.h>

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define MOVEVALUE 5

Character& Character::getInstance()
{
	static Character charac;
	return charac;
}

Character::Character() : Creature(100, 1, 1, NULL)
{	
	mColor = al_map_rgb(0, 0, 255);
	mSkin = al_load_bitmap("skin\\terr.png");
	Weapon tmp("Webley Revolver", mColor, 20, 24, 6, 1, false);
	mGun = tmp;
}

void Character::move(const ALLEGRO_KEYBOARD_STATE key)
{
	int dir = 0;
	int run = 0;
	if (al_key_down(&key, ALLEGRO_KEYMOD_SHIFT))
		run = 5;
	if (al_key_down(&key, ALLEGRO_KEY_UP))
		dir = UP;
	if (al_key_down(&key, ALLEGRO_KEY_DOWN))
		dir = DOWN;
	if (al_key_down(&key, ALLEGRO_KEY_RIGHT))
		dir = RIGHT;
	if (al_key_down(&key, ALLEGRO_KEY_LEFT))
		dir = LEFT;

	if (dir == UP && mCordY <= 0)
		return;
	if (dir == DOWN && mBoxY >= 708)
		return;
	if (dir == LEFT && mCordX <= -12)
		return;
	if (dir == RIGHT && mBoxX >= 1251)
		return;

	if(dir)
		mMovDir = dir;

	switch (dir)
	{
	case UP:
		mCordY -= (MOVEVALUE + run);
		mBoxY -= (MOVEVALUE + run);
		break;
	case DOWN:
		mCordY += (MOVEVALUE + run);
		mBoxY += (MOVEVALUE + run);
		break;
	case LEFT:
		mCordX -= (MOVEVALUE + run);
		mBoxX -= (MOVEVALUE + run);
		break;
	case RIGHT:
		mCordX += (MOVEVALUE + run);
		mBoxX += (MOVEVALUE + run);
		break;
	}

}
