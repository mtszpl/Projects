#include "Thing.h"

Thing::Thing(int x, int y, char type)
{
	mType = type;
	mCordX = x;
	mCordY = y;
	switch (type)
	{
	case('a'):
		mTexture = al_load_bitmap("assets\\air32.png");
		break;
	case('o'):
		mTexture = al_load_bitmap("assets\\boulder32.png");
		break;
	case('i'):
		mTexture = al_load_bitmap("assets\\diamond32.png");
		break;
	case('d'):
		mTexture = al_load_bitmap("assets\\dirt32.png");
		break;
	case('p'):
		mTexture = al_load_bitmap("assets\\pc32.png");
		break;
	case('b'):
		mTexture = al_load_bitmap("assets\\bricks32.png");
		break;
	case('e'):
		mTexture = al_load_bitmap("assets\\dirt32.png");
		break;
	case('l'):
		mTexture = al_load_bitmap("assets\\amoeba32.png");
		break;
	default:
		break;

	}
}

Thing::Thing()
{
	mType = 0;
	mCordX = -1;
	mCordY = -1;
	mTexture = nullptr;
}

int Thing::getCordX()
{
	return mCordX;
}

int Thing::getCordY()
{
	return mCordY;
}

ALLEGRO_BITMAP* Thing::getTexture()
{
	return mTexture;
}

char Thing::getType()
{
	return mType;
}

void Thing::draw()
{
	al_draw_bitmap(mTexture, mCordX, mCordY, 0);
	al_flip_display();
}

bool Thing::correctType()
{
	switch (mType)
	{
	case 'a':
		return true;
		break;
	case 'd':
		return true;
		break;
	case 'i':
		return true;
		break;
	case 'e':
		return true;
		break;
	default:
		return false;
	}
}

void Thing::operator=(Thing _t)
{
	mCordX = _t.mCordX;
	mCordY = _t.mCordY;
	mType = _t.mType;
	switch (mType)
	{
	case('a'):
		mTexture = al_load_bitmap("assets\\air32.png");
		break;
	case('o'):
		mTexture = al_load_bitmap("assets\\boulder32.png");
		break;
	case('i'):
		mTexture = al_load_bitmap("assets\\diamond32.png");
		break;
	case('d'):
		mTexture = al_load_bitmap("assets\\dirt32.png");
		break;
	case('p'):
		mTexture = al_load_bitmap("assets\\pc32.png");
		break;
	case('b'):
		mTexture = al_load_bitmap("assets\\bricks32.png");
		break;
	case('e'):
		mTexture = al_load_bitmap("assets\\dirt32.png");
		break;
	case('l'):
		mTexture = al_load_bitmap("assets\\amoeba32.png");
		break;
	default:
		break;
	}
}

