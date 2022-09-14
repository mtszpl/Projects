#include "MainWindow.h"

MainWindow::MainWindow()
{
	al_init();
	al_init_image_addon();
	al_init_primitives_addon();
	mDisplay = al_create_display(1280, 708);
	al_install_keyboard();
	mGameEnd = false;
}

MainWindow::~MainWindow()
{
	al_destroy_display(mDisplay);
	al_uninstall_keyboard();
}

void MainWindow::run()
{
	Game theGame;
	theGame.run(mGameEnd, mDisplay);
}