#pragma once
#include "Thing.h"
class Terrain :
	public Thing
{
public:
	/**Tworzy obiekt o zadanych wsp�rz�dnych i zadanym typie. Dziedziczy po konstruktorze obiektu Thing
	* @param x Wsp�rz�dna x
	* @param y Wsp�rz�dna y
	* @param type Typ nowego obiektu
	*/
	Terrain(int x, int y, char type);
	/**Tworzy obiekt nieznanego typu o wsp�rz�dnych -1, -1, typo 0
	*/
	Terrain();

	/**Zamienia typ obiektu z lawy na kamie�
	* @param amount Ilo�� lawy na planszy
	*/
	void amoebaToBoulder(int& amount);
	/**Zamienia typ obiektu z lawy na diament
	* @param amountA Ilo�� lawy na planszy
	* @param amountD Ilo�� diament�w na planszy
	*/
	void amoebaToDiamond(int& amountA, int& amountD);
	/**Je�li to mo�liwe, zmienia typ obiektu na law�
	* @param amount Ilo�� lawy na planszy
	*/
	void grow(int& amount);
	/**Zamienia typ obiektu na zadany
	* @param newType Nowy typ obiektu.
	*/
	void change(char newType);
};

