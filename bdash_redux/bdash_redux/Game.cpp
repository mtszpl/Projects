#include <fstream>
#include <string>
#include <iostream>

#include "Game.h"
#include "Terrain.h"

Game::Game(Character& player, std::string level)
{
	std::fstream map;
	std::string line;
	mPlayerCordX = -1;
	mPlayerCordY = -1;
	mDoorCordX = -1;
	mDoorCordY = -1;
	mScore = 0;
	mLevel = level[6] - 48;

	int row = 0;

	mDiamonds = 0;
	mAmoeba = 0;

	map.open(level); // plik przechowuj¹cy mapê poziomu


	board = new Terrain* [40];
	mSizeX = 40;
	for (int i = 0; i < 40; i++)
		board[i] = new Terrain[22];
	mSizeY = 22;
	
	while (map.eof() != true)
	{
		map >> line;
		for (int col = 0; col < 40; col++)
		{
			if (line[col] == 'p')
			{
				Character newPlayer(col * 32, row * 32);
				player = newPlayer;
				board[col][row] = Terrain(col * 32, row * 32, line[col]);
				mPlayerCordX = col;
				mPlayerCordY = row;
			}
			else
			{
				board[col][row] = Terrain(col * 32, row * 32, line[col]);
				if (line[col] == 'i')
					mDiamonds++;
				if(line[col] == 'l')
					mAmoeba++;
				if (line[col] == 'e')
				{
					mDoorCordX = col;
					mDoorCordY = row;
				}
			}
		}
		row++;
	}

	map.close();
}

Game::~Game()
{
	for (int i = 0; i < 40; i++)
	{
		delete[] board[i];
		board[i] = nullptr;
	}
	delete[] board;
}

int Game::getDiamonds()
{
	return mDiamonds;
}

int Game::getLevel()
{
	return mLevel;
}

void Game::draw()
{
	for(int i = 0; i < mSizeY; i++)
		for (int j = 0; j < mSizeX; j++)
		{
			if (j == mPlayerCordX && i == mPlayerCordY)
				j++;
			board[j][i].draw();
		}

}

void Game::move(ALLEGRO_KEYBOARD_STATE &key, Character* player)
{

	if (al_key_down(&key, ALLEGRO_KEY_RIGHT) && mPlayerCordX < mSizeX)
	{
		if (board[mPlayerCordX + 1][mPlayerCordY].correctType())
		{
			if (board[mPlayerCordX + 1][mPlayerCordY].getType() == 'i')
			{
				mScore++;
				mDiamonds--;
			}
			board[mPlayerCordX][mPlayerCordY].change('a');
			board[mPlayerCordX + 1][mPlayerCordY].change('a');

			player->move(2);
			player->draw();
			board[mPlayerCordX][mPlayerCordY].draw();
			board[mPlayerCordX + 2][mPlayerCordY].draw();
			mPlayerCordX++;
		}
		else if (board[mPlayerCordX + 1][mPlayerCordY].getType() == 'o')
		{
			if(board[mPlayerCordX +2][mPlayerCordY].getType() == 'a')
			{ 
				board[mPlayerCordX][mPlayerCordY].change('a');
				board[mPlayerCordX + 1][mPlayerCordY].change('a');
				board[mPlayerCordX + 2][mPlayerCordY].change('o');

				player->move(2);
				player->draw();
				board[mPlayerCordX][mPlayerCordY].draw();
				board[mPlayerCordX + 2][mPlayerCordY].draw();
				mPlayerCordX++;
			}
		}
		
	}
	if (al_key_down(&key, ALLEGRO_KEY_LEFT) && mPlayerCordX > 0)
	{
		if (board[mPlayerCordX - 1][mPlayerCordY].correctType())
		{
			if (board[mPlayerCordX - 1][mPlayerCordY].getType() == 'i')
			{
				mScore++;
				mDiamonds--;
			}
			board[mPlayerCordX][mPlayerCordY].change('a');
			board[mPlayerCordX - 1][mPlayerCordY].change('a');

			player->move(1);
			player->draw();
			board[mPlayerCordX][mPlayerCordY].draw();
			mPlayerCordX--;
		}
		else if (board[mPlayerCordX - 1][mPlayerCordY].getType() == 'o')
		{
			if (board[mPlayerCordX - 2][mPlayerCordY].getType() == 'a')
			{
				board[mPlayerCordX][mPlayerCordY].change('a');
				board[mPlayerCordX - 1][mPlayerCordY].change('a');
				board[mPlayerCordX - 2][mPlayerCordY].change('o');

				player->move(1);
				player->draw();
				board[mPlayerCordX][mPlayerCordY].draw();
				board[mPlayerCordX - 2][mPlayerCordY].draw();
				mPlayerCordX--;
			}
		}
	}
	if (al_key_down(&key, ALLEGRO_KEY_DOWN) && mPlayerCordY < mSizeY)
	{
		if (board[mPlayerCordX][mPlayerCordY + 1].correctType())
		{
			if (board[mPlayerCordX][mPlayerCordY + 1].getType() == 'i')
			{
				mScore++;
				mDiamonds--;
			}
			board[mPlayerCordX][mPlayerCordY].change('a');
			board[mPlayerCordX][mPlayerCordY + 1].change('a');

			player->move(4);

			player->draw();
			board[mPlayerCordX][mPlayerCordY].draw();

			mPlayerCordY++;
		}
	}
	if (al_key_down(&key, ALLEGRO_KEY_UP) && mPlayerCordY > 0)
	{
		if (board[mPlayerCordX][mPlayerCordY - 1].correctType())
		{
			if (board[mPlayerCordX][mPlayerCordY - 1].getType() == 'i')
			{
				mScore++;
				mDiamonds--;
			}
			board[mPlayerCordX][mPlayerCordY].change('a');
			board[mPlayerCordX][mPlayerCordY - 1].change('a');

			player->move(3);

			player->draw();
			board[mPlayerCordX][mPlayerCordY].draw();

			mPlayerCordY--;
		}
	}
}

void Game::showDoor()
{
	if (mDiamonds == 0 && mAmoeba == 0)
	{
		board[mDoorCordX][mDoorCordY].change('e');
		int x = board[mDoorCordX][mDoorCordY].getCordX();
		int y = board[mDoorCordX][mDoorCordY].getCordY();
		al_draw_bitmap(board[mDoorCordX][mDoorCordY].getTexture(), x, y, 0);
		al_flip_display();
	}
}

void Game::itemFall()
{
	for (int i = 1; i < mSizeX; i++)
	{
		for (int j = 1; j < mSizeY; j++)
		{
			char type = board[i][j].getType();
			if (type == 'o' || type == 'i')
			{
				if ((board[i][j + 1].getType() == 'a') && !(mPlayerCordX == i && mPlayerCordY - 1 == j))
				{
					board[i][j + 1].change(type);
					board[i][j].change('a');
					al_draw_bitmap(board[i][j + 1].getTexture(), board[i][j + 1].getCordX(), board[i][j + 1].getCordY(), 0);
					al_draw_bitmap(board[i][j].getTexture(), board[i][j].getCordX(), board[i][j].getCordY(), 0);
					al_flip_display();
				}
				else 
				{
					bool side = true;
					if ((mPlayerCordX == i + 1 && mPlayerCordY == j + 1) || (mPlayerCordX == i + 1 && mPlayerCordY == j))
						side = false;
					if (board[i + 1][j].getType() == 'a' && board[i + 1][j + 1].getType() == 'a' && side == true)
					{
						board[i + 1][j].change(type);
						board[i][j].change('a');
						al_draw_bitmap(board[i + 1][j].getTexture(), board[i + 1][j].getCordX(), board[i + 1][j].getCordY(), 0);
						al_draw_bitmap(board[i][j].getTexture(), board[i][j].getCordX(), board[i][j].getCordY(), 0);
						al_flip_display();
						i++;
					}
					if ((mPlayerCordX == i - 1 && mPlayerCordY == j + 1) || (mPlayerCordX == i - 1 && mPlayerCordY == j))
						side = false;
					if (board[i - 1][j].getType() == 'a' && board[i - 1][j + 1].getType() == 'a' && side == true)
					{
						board[i - 1][j].change(type);
						board[i][j].change('a');
						al_draw_bitmap(board[i - 1][j].getTexture(), board[i - 1][j].getCordX(), board[i - 1][j].getCordY(), 0);
						al_draw_bitmap(board[i][j].getTexture(), board[i][j].getCordX(), board[i][j].getCordY(), 0);
						al_flip_display();
					}
				}
			}
		}
	}
}

int Game::amoebaGrow()
{
	if (mAmoeba == 0)
		return 0;
	int counter = 0;
	for (int i = 1; i < mSizeX - 1; i++)
	{
		for (int j = 1; j < mSizeY - 1; j++)
		{
			if (board[i][j].getType() == 'l')
			{
				if ((board[i + 1][j].getType() != 'a' && board[i + 1][j].getType() != 'd') && \
					(board[i - 1][j].getType() != 'a' && board[i - 1][j].getType() != 'd') && \
					(board[i][j + 1].getType() != 'a' && board[i][j + 1].getType() != 'd') && \
					(board[i][j - 1].getType() != 'a' && board[i][j - 1].getType() != 'd'))
						counter++;
				else
				{
					int dir = rand() % 5; // l r u d
					switch (dir)
					{
					case 0:
						break;
					case 1:
						board[i + 1][j].grow(mAmoeba);
						break;
					case 2:
						board[i - 1][j].grow(mAmoeba);
						break;
					case 3:
						board[i][j - 1].grow(mAmoeba);
						break;
					case 4:
						board[i][j + 1].grow(mAmoeba);
						break;

					}
				}
			}
		}
	}
	return counter;
}

void Game::checkGrow(const int blockedAmo)
{
	if (mAmoeba == 0)
		return;
	if (mAmoeba >= 200)
	{
		for (int i = 1; i < mSizeX - 1; i++)
			for (int j = 1; j < mSizeY - 1; j++)
				board[i][j].amoebaToBoulder(mAmoeba);
		mAmoeba = 0;
	}
	else if(blockedAmo == mAmoeba)
	{
		for (int i = 1; i < mSizeX - 1; i++)
			for (int j = 1; j < mSizeY - 1; j++)
				board[i][j].amoebaToDiamond(mAmoeba, mDiamonds);
		mAmoeba = 0;
	}
}

bool Game::nextLevel(std::string& level)
{
	if (mAmoeba == 0 && mDiamonds == 0)
	{
		if (mDoorCordX == mPlayerCordX && mDoorCordY == mPlayerCordY)
		{
			mLevel++;
			char c = mLevel + 48;
			level[level.size() - 5] = c;
			return true;
		}
	}
	return false;
}

void Game::operator=(Game& _g)
{
	mPlayerCordX = _g.mPlayerCordX;
	mPlayerCordY = _g.mPlayerCordY;
	mDoorCordX = _g.mDoorCordX;
	mDoorCordY = _g.mDoorCordY;
	mScore = _g.mScore;
	mLevel = _g.mLevel;
	mDiamonds = _g.mDiamonds;
	mAmoeba = _g.mAmoeba;
	for (int i = 0; i < mSizeX; i++)
	{
		for (int j = 0; j < mSizeY; j++)
		{
			board[i][j] = _g.board[i][j];
		}
	}
}