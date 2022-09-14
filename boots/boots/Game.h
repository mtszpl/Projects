#pragma once
#include <deque>

#include "Bullet.h"
#include "Weapon.h"
#include "Enemy.h"
#include "Character.h"

class Game
{
private:
	bool mGameEnd;
	std::vector<Bullet*> mBulletsShot;
	std::vector<Bullet*> mEnemyShot;
	std::vector<Enemy*> mEnemies;
	Character mPc;

	ALLEGRO_EVENT mEventIn;
	ALLEGRO_KEYBOARD_STATE mKey;

	ALLEGRO_EVENT_QUEUE* mQueue;
	ALLEGRO_TIMER* mTimer;

public:
	Game();
	~Game();

	void run(bool& ended, ALLEGRO_DISPLAY* display);
	void bulletFly(Bullet& projectile);

	void enemyLifeCycle();

	void playerShoot();
	void npcShoot(int index);
};

