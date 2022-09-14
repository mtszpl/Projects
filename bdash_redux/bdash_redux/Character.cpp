#include "Character.h"

Character::Character(int x, int y) : Thing(x, y, 'p')
{
	mPlayerCordX = mCordX / 32;
	mPlayerCordY = mCordY / 32;
}

Character::Character() : Thing()
{
	mPlayerCordX = -1;
	mPlayerCordY = -1;
	mTexture = al_load_bitmap("assets\\pc32.png");
}

void Character::move(int dir) // 1 -left 2 - right 3 - up 4 - down
{
	int x = al_get_bitmap_width(mTexture);
	int y = al_get_bitmap_height(mTexture);

	switch(dir)
	{
	case (1):
		mCordX -= x;
		mPlayerCordX--;
		break;
	case (2):
		mCordX += x;
		mPlayerCordX++;
		break;
	case (3):
		mCordY -= y;
		mPlayerCordY--;
		break;
	case (4):
		mCordY += y;
		mPlayerCordY++;
		break;
	}
}
