#pragma once
#include "Structs.h"

/**Funkcja wype³nia pierwotn¹ planszê do gry.
@param board Wype³niana plansza.
*/
void setBoard(struct Board* board);

/**Funkcja wypisuje planszê do gry.
@param board Wypisywana plansza
*/
void drawBoard(struct Board* board);

/**Funkcja odpowiada za przesuwanie kursora lub przeskoku kamienia w górê.
@param board Plansza
*/
void moveUp(struct Board* board);

/**Funkcja odpowiada za przesuwanie kursora lub przeskoku kamienia w dó³.
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

/**Funckcja sprawdza, czy gra zosta³a wygrana.
@param board Plansza
*/
void isWon(struct Board* board);

/**Funckja sprawdza, czy gra zosta³a przegrana.
@param board Plansza
*/
void isLost(struct Board* board);

/**Funkcja sprawdza, czy s¹mo¿liwe kolejny ruchy z okreœlonej pozycji.
@param board Plansza
@param x @param y Pozycja
*/
int checkForOptions(struct Board* board, int x, int y);

/**Fubkcja wczytuje listê wyników z pliku 
*/
struct score* openScore();

/**Funkcja dodaje nowy wynik do listy
@param scr Lista wyników
@param nwScore Nowy wynik dodawany do listy
*/
struct score* saveScore(struct score* scr, struct score* nwScore);

/**Funkcja wyœwietla listê wyników
@param scr Wyœwietlana lista wyników
*/
void printScore(const struct score* scr);

/**Funkcja liczy i zapisuje wynik
@param b Plansza gry
@param scoreBoard Lista wyników
*/
void endGame(struct Board b,  struct score* scoreBoard);

/**Funkcja usuwa listê wyników
@param scr Usuwana lista wyników
*/
void closeScore(struct score* scr);