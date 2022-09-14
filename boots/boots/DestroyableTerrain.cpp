#include "DestroyableTerrain.h"

DestroyableTerrain::DestroyableTerrain()
{
	mColor = al_map_rgb(255, 255, 255);
	mTraversable = false;
	mSkin = NULL;
	type = 'r';
}

void DestroyableTerrain::damage(int dmg)
{
	mHp -= dmg;
}