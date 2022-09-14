#pragma once
#include "Thing.h"
class Terrain :
	public Thing
{
public:
	/**Tworzy obiekt o zadanych wspó³rzêdnych i zadanym typie. Dziedziczy po konstruktorze obiektu Thing
	* @param x Wspó³rzêdna x
	* @param y Wspó³rzêdna y
	* @param type Typ nowego obiektu
	*/
	Terrain(int x, int y, char type);
	/**Tworzy obiekt nieznanego typu o wspó³rzêdnych -1, -1, typo 0
	*/
	Terrain();

	/**Zamienia typ obiektu z lawy na kamieñ
	* @param amount Iloœæ lawy na planszy
	*/
	void amoebaToBoulder(int& amount);
	/**Zamienia typ obiektu z lawy na diament
	* @param amountA Iloœæ lawy na planszy
	* @param amountD Iloœæ diamentów na planszy
	*/
	void amoebaToDiamond(int& amountA, int& amountD);
	/**Jeœli to mo¿liwe, zmienia typ obiektu na lawê
	* @param amount Iloœæ lawy na planszy
	*/
	void grow(int& amount);
	/**Zamienia typ obiektu na zadany
	* @param newType Nowy typ obiektu.
	*/
	void change(char newType);
};

