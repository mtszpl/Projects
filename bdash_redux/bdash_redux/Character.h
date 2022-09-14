#pragma once
#include "Thing.h"
class Character :
	public Thing
{
private:
	int mPlayerCordX;
	int mPlayerCordY;

public:
	/**Tworzy obiekt o zadanych wspó³rzêdnych
	* @param x Wspó³rzêdna x
	* @param y Wspó³rzêdna y
	*/
	Character(int x, int y);
	/**Tworzy obiekt o wspó³rzêdnych -1, -1
	*/
	Character();

	/**Zmienia wspó³rzêdne przy ruchu
	* @param dir Kierunek ruchu 1- lewo, 2 - prawo, 3 - góra, 4 - dó³
	*/
	void move(int dir);
};

