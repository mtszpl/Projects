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
	* @param x Wspó³rzêdna x
	* @param y Wspó³rzêdna y
	* @param type Typ nowego obiektu
	*/
	Thing(int x, int y, char type);
	/**Tworzy obiekt nieznanego typu o wspó³rzêdnych -1, -1, typu 0
	*/
	Thing();

	/**Zwraca wartoœæ mCordX
	*/
	int getCordX();
	/**Zwraca wartoœæ mCordY
	*/
	int getCordY();
	/**Zwraca wartoœæ mType
	*/
	char getType();
	/**Zwraca wskaŸnik na wartoœæ mTexture
	*/
	ALLEGRO_BITMAP* getTexture();

	/**Sprawdza, czy gracz mo¿e ruszyæ siê na to pole. Zwraca true, jeœli tak, false jeœl nie.
	*/
	bool correctType();
	/**Wyœwietla teksturêprzechowywan¹w mTexture
	*/
	void draw();

	/**Ustawia wartoœci obiektu po lewej stronie operatora na identyczne jak obiektu po prawej stronie.
	* @param _t Obiekt po prawej stronie
	*/
	void operator=(Thing _t);
};

