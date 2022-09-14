#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Thing
{
protected:
	int mCordX;
	int mCordY;
	char mType;
	ALLEGRO_BITMAP* mTexture;

public:
	/**Tworzy obiekt danego typu o zadanych parametrach
	* @param x Wsp�rz�dna x
	* @param y Wsp�rz�dna y
	* @param type Typ nowego obiektu
	*/
	Thing(int x, int y, char type);
	/**Tworzy obiekt nieznanego typu o wsp�rz�dnych -1, -1, typu 0
	*/
	Thing();

	/**Zwraca warto�� mCordX
	*/
	int getCordX();
	/**Zwraca warto�� mCordY
	*/
	int getCordY();
	/**Zwraca warto�� mType
	*/
	char getType();
	/**Zwraca wska�nik na warto�� mTexture
	*/
	ALLEGRO_BITMAP* getTexture();

	/**Sprawdza, czy gracz mo�e ruszy� si� na to pole. Zwraca true, je�li tak, false je�l nie.
	*/
	bool correctType();
	/**Wy�wietla tekstur�przechowywan�w mTexture
	*/
	void draw();

	/**Ustawia warto�ci obiektu po lewej stronie operatora na identyczne jak obiektu po prawej stronie.
	* @param _t Obiekt po prawej stronie
	*/
	void operator=(Thing _t);
};

