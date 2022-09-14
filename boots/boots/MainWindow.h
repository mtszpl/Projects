#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include "Game.h"

class MainWindow
{
private:
	ALLEGRO_DISPLAY* mDisplay;

	bool mGameEnd;

public:
	MainWindow();
	~MainWindow();

	void run();
};

