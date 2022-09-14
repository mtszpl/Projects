#pragma once
#include "Thing.h"
class Character :
	public Thing
{
private:
	int mPlayerCordX;
	int mPlayerCordY;

public:
	/**Tworzy obiekt o zadanych wsp�rz�dnych
	* @param x Wsp�rz�dna x
	* @param y Wsp�rz�dna y
	*/
	Character(int x, int y);
	/**Tworzy obiekt o wsp�rz�dnych -1, -1
	*/
	Character();

	/**Zmienia wsp�rz�dne przy ruchu
	* @param dir Kierunek ruchu 1- lewo, 2 - prawo, 3 - g�ra, 4 - d�
	*/
	void move(int dir);
};

