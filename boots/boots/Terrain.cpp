#include "Terrain.h"

Terrain::Terrain()
{
	mColor = al_map_rgb(0, 255, 0);
	mTraversable = true;
	mSkin = NULL;
	type = 'g';
}

void Terrain::draw(int corX, int corY)
{
	if (mSkin == nullptr)
		al_draw_rectangle(corX, corY, corX + 64, corY + 64, mColor, 2.0);
	else
		al_draw_bitmap(mSkin, corX, corY, NULL);
}

bool Terrain::isTraversable()
{
	return mTraversable;
}