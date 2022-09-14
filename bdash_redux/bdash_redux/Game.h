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
	/**Tworzy plansz� danego poziomu i posta� gracza
	* @param player Posta� gracza
	* @param level Nazwa pliku z map� poziomu
	*/
	Game(Character& player, std::string level);
	/**Niszczy obiekt
	*/
	~Game();

	/**Wy�wietla plansz�
	*/
	void draw();
	/**Przemieszcza posta� gracza. W miar� potrzeby, przesuwa kamienie lub zbiera diamenty.
	* @param key Wci�ni�ty klawisz
	* @param player Przemieszczana posta� gracza
	*/
	void move(ALLEGRO_KEYBOARD_STATE &key, Character* player);

	/**Zwraca ilo�� diament�w na mapie
	*/
	int getDiamonds();
	/**Zwraca aktualny poziom
	*/
	int getLevel();

	/**Zmienia tekstur� wyj�cia
	*/
	void showDoor();
	/**Odpowiada za rozrost lawy na planszy. Zwraca ilo�� obiekt�w typu lawa, kt�re nie mog� si� dalej rozrasta�.
	*/
	int amoebaGrow();
	/**Sprawdza, czy lawa mo�e si� dalej rozrasta� i czy ilo�� obiekt�w tego typu przekroczy�a 200.
	* Je�li nie mo�e si� dalej rozrasta�, zamienia ca�� law� w diamenty,
	* je�li przekroczy�a 200, zamienia ca�� law� w ska�y
	*/
	void checkGrow(const int blockedAmo);
	/**Odpowiada za upadek kamieni i diament�w.
	*/
	void itemFall();
	/**Sprawdza czy poziom zosta� uko�czony. Je�li tak, zmienia odpowiednio argument funkcji.
	* @param level Nazwa pliku przechowuj�cego map� poziomu.
	*/
	bool nextLevel(std::string& level);

	/**Ustawia atrybuty obiektu po lewej stronie operatora na identyczne jak obiektu po prawej stronie.
	* @param _g Obiekt po prawej stronie.
	*/
	void operator=(Game& _g);
};

