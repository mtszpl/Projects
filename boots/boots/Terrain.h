#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

class Terrain
{
protected:
	char type;
	ALLEGRO_BITMAP* mSkin;
	ALLEGRO_COLOR mColor;
	bool mTraversable;
public:
	Terrain();

	void draw(int corX, int corY);

	bool isTraversable();
};

