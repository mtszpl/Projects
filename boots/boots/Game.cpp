#include "Game.h"

#include <iostream>

Game::Game()
{
	mGameEnd = false;
	mQueue = al_create_event_queue();
	mTimer = al_create_timer(02.0 / 60);

	al_register_event_source(mQueue, al_get_keyboard_event_source());
	al_register_event_source(mQueue, al_get_timer_event_source(mTimer));
}

Game::~Game()
{
	mGameEnd = true;
	al_destroy_event_queue(mQueue);
	al_destroy_timer(mTimer);
}

void Game::run(bool& ended, ALLEGRO_DISPLAY* display)
{
	al_register_event_source(mQueue, al_get_display_event_source(display));
	al_start_timer(mTimer);

	mGameEnd = ended;
#ifdef _DEBUG
	Enemy enem1(100, 500, 100, 'b');
	Enemy enem2(100, 600, 350, 'b');
	mEnemies.push_back(&enem1);
	mEnemies.push_back(&enem2);
#endif

	while (!mGameEnd)
	{
		al_wait_for_event(mQueue, &mEventIn);
		al_get_keyboard_state(&mKey);

		if (mEventIn.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			mGameEnd = true;
		if (mEventIn.type == ALLEGRO_EVENT_TIMER)
		{
			if (ALLEGRO_EVENT_KEY_DOWN)
			{
				mPc.move(mKey);
				if (al_key_down(&mKey, ALLEGRO_KEY_LCTRL) && mPc.getWeapon().isAuto() == true)
					playerShoot();
			}

			std::vector<Bullet*>::iterator bullet = mBulletsShot.begin();
			while(bullet != mBulletsShot.end())
			{
				bulletFly(**bullet);
				for (int i = 0; i < mEnemies.size(); i++)
					(*bullet)->hit(*mEnemies[i]);
				if ((*bullet)->getFly() == false)
				{
					delete *bullet;
					bullet=mBulletsShot.erase(bullet);
					continue;
				}
				++bullet;
			}
			bullet = mEnemyShot.begin();
			while (bullet != mEnemyShot.end())
			{
				bulletFly(**bullet);
				(*bullet)->hit(mPc);
				if ((*bullet)->getFly() == false)
				{
					delete* bullet;
					bullet = mEnemyShot.erase(bullet);
					continue;
				}
				++bullet;
			}

			enemyLifeCycle();
		}
		if (mEventIn.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (al_key_down(&mKey, ALLEGRO_KEY_LCTRL) && mPc.getWeapon().isAuto() == false)
				playerShoot();
			if (al_key_down(&mKey, ALLEGRO_KEY_R))
				mPc.reload();
		}

		mPc.draw();

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
}

void Game::bulletFly(Bullet& projectile)
{

	if (projectile.getFly() != false)
		projectile.letFly();
}

void Game::enemyLifeCycle()
{
	for (int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->setMoveDir();
		mEnemies[i]->monitor(mPc);
		npcShoot(i);
		if (mEnemies[i]->getWeapon().isFullMag() == false)
			mEnemies[i]->reload();
		mEnemies[i]->draw();
	}
}

void Game::playerShoot()
{
	Bullet* b = mPc.shoot();
	if (b != nullptr && b->getFly() == true)
		mBulletsShot.push_back(b);
}

void Game::npcShoot(int index)
{
	Bullet* b = mEnemies[index]->attack(mPc);
	if (b != nullptr && b->getFly() == true)
		mEnemyShot.push_back(b);
}