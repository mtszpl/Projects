#pragma once
#include "Structs.h"

/**Funkcja wype�nia pierwotn� plansz� do gry.
@param board Wype�niana plansza.
*/
void setBoard(struct Board* board);

/**Funkcja wypisuje plansz� do gry.
@param board Wypisywana plansza
*/
void drawBoard(struct Board* board);

/**Funkcja odpowiada za przesuwanie kursora lub przeskoku kamienia w g�r�.
@param board Plansza
*/
void moveUp(struct Board* board);

/**Funkcja odpowiada za przesuwanie kursora lub przeskoku kamienia w d�.
@param board Plansza
*/
void moveDown(struct Board* board);

/**Funkcja odpowiada za przesuwanie kursora lub przeskoku kamienia w lewo.
@param board Plansza
*/
void moveLeft(struct Board* board);

/**Funkcja odpowiada za przesuwanie kursora lub przeskoku kamienia w prawo.
@param board Plansza
*/
void moveRight(struct Board* board);

/**Funckcja sprawdza, czy gra zosta�a wygrana.
@param board Plansza
*/
void isWon(struct Board* board);

/**Funckja sprawdza, czy gra zosta�a przegrana.
@param board Plansza
*/
void isLost(struct Board* board);

/**Funkcja sprawdza, czy s�mo�liwe kolejny ruchy z okre�lonej pozycji.
@param board Plansza
@param x @param y Pozycja
*/
int checkForOptions(struct Board* board, int x, int y);

/**Fubkcja wczytuje list� wynik�w z pliku 
*/
struct score* openScore();

/**Funkcja dodaje nowy wynik do listy
@param scr Lista wynik�w
@param nwScore Nowy wynik dodawany do listy
*/
struct score* saveScore(struct score* scr, struct score* nwScore);

/**Funkcja wy�wietla list� wynik�w
@param scr Wy�wietlana lista wynik�w
*/
void printScore(const struct score* scr);

/**Funkcja liczy i zapisuje wynik
@param b Plansza gry
@param scoreBoard Lista wynik�w
*/
void endGame(struct Board b,  struct score* scoreBoard);

/**Funkcja usuwa list� wynik�w
@param scr Usuwana lista wynik�w
*/
void closeScore(struct score* scr);