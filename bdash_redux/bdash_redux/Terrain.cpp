#include "Terrain.h"

Terrain::Terrain(int x, int y, char type) : Thing (x, y, type)
{

}

Terrain::Terrain() : Thing()
{

}

void Terrain::amoebaToBoulder(int& amount)
{
	if (mType == 'l')
	{
		mType = 'o';
		mTexture = al_load_bitmap("assets\\boulder32.png");
		draw();
		amount--;
	}
}

void Terrain::amoebaToDiamond(int& amountA, int& amountD)
{
	if (mType == 'l')
	{
		mType = 'i';
		mTexture = al_load_bitmap("assets\\diamond32.png");
		draw();
		amountA--;
		amountD++;
	}
}

void Terrain::grow(int& amount)
{
	if (mType == 'a' || mType == 'd')
	{
		mType = 'l';
		mTexture = al_load_bitmap("assets\\amoeba32.png");
		draw();
		amount++;
	}
}


void Terrain::change(char newType)
{
	switch (newType)
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
	case('b'):
		mTexture = al_load_bitmap("assets\\bricks32.png");
		break;
	case('l'):
		mTexture = al_load_bitmap("assets\\amoeba32.png");
		break;
	case('e'):
		mTexture = al_load_bitmap("assets\\door32.png");
		break;
	default:
		break;
	}

	mType = newType;
}

