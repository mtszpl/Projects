#pragma once
#include "Thing.h"
#include "Character.h"
#include "Terrain.h"

class Game
{
private:
	Terrain** board; // 40 x 22
	int mSizeX;
	int mSizeY;

	int mPlayerCordX;
	int mPlayerCordY;
	int mDoorCordX;
	int mDoorCordY;

	int mDiamonds;
	int mAmoeba;
	int mScore;
	int mLevel;

public:
	/**Tworzy planszê danego poziomu i postaæ gracza
	* @param player Postaæ gracza
	* @param level Nazwa pliku z map¹ poziomu
	*/
	Game(Character& player, std::string level);
	/**Niszczy obiekt
	*/
	~Game();

	/**Wyœwietla planszê
	*/
	void draw();
	/**Przemieszcza postaæ gracza. W miarê potrzeby, przesuwa kamienie lub zbiera diamenty.
	* @param key Wciœniêty klawisz
	* @param player Przemieszczana postaæ gracza
	*/
	void move(ALLEGRO_KEYBOARD_STATE &key, Character* player);

	/**Zwraca iloœæ diamentów na mapie
	*/
	int getDiamonds();
	/**Zwraca aktualny poziom
	*/
	int getLevel();

	/**Zmienia teksturê wyjœcia
	*/
	void showDoor();
	/**Odpowiada za rozrost lawy na planszy. Zwraca iloœæ obiektów typu lawa, które nie mog¹ siê dalej rozrastaæ.
	*/
	int amoebaGrow();
	/**Sprawdza, czy lawa mo¿e siê dalej rozrastaæ i czy iloœæ obiektów tego typu przekroczy³a 200.
	* Jeœli nie mo¿e siê dalej rozrastaæ, zamienia ca³¹ lawê w diamenty,
	* jeœli przekroczy³a 200, zamienia ca³¹ lawê w ska³y
	*/
	void checkGrow(const int blockedAmo);
	/**Odpowiada za upadek kamieni i diamentów.
	*/
	void itemFall();
	/**Sprawdza czy poziom zosta³ ukoñczony. Jeœli tak, zmienia odpowiednio argument funkcji.
	* @param level Nazwa pliku przechowuj¹cego mapê poziomu.
	*/
	bool nextLevel(std::string& level);

	/**Ustawia atrybuty obiektu po lewej stronie operatora na identyczne jak obiektu po prawej stronie.
	* @param _g Obiekt po prawej stronie.
	*/
	void operator=(Game& _g);
};

