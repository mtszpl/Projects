#include <malloc.h>
#include <assert.h>

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <crtdbg.h>
#include <locale.h>
#include "Structs.h"
#include "Funcs.h"

int main()
{
	int heapstatus = 0;
	{
		setlocale(LC_CTYPE, "Polish");
		struct score* scoreBoard = NULL;
		scoreBoard = openScore();
		assert(_CrtCheckMemory());
		struct Board b;
		b.isSelected = 0;
		b.won = 0;
		setBoard(&b);
		drawBoard(&b);
		printf("q - wyjœcie\nr - reset\n");
		while (b.won == 0)
		{
			char c = 0;
			c = _getch();
			if (c == -32)
				c = _getch();
			switch (c)
			{
			case 72:
				moveUp(&b); break;
			case 80:
				moveDown(&b); break;
			case 75:
				moveLeft(&b); break;
			case 77:
				moveRight(&b); break;
			case 13:
				if (b.isSelected == 1)
					b.isSelected = 0;
				else if (b.isSelected == 0 && b.board[b.pose.x][b.pose.y] != '.')
					b.isSelected = 1;
				break;
			case 114:
				setBoard(&b); break;
			case 113:
				endGame(b, scoreBoard);
				printf("%d", _CrtDumpMemoryLeaks());
				return 0; break;
			}
			system("cls");
			drawBoard(&b);
			printf("q - wyjœcie\nr - reset\n");
			isWon(&b);
			isLost(&b);
			if (b.won == -1)
			{
				printf("Pora¿ka!");
				endGame(b, scoreBoard);
				printf("\nZagraæ ponownie? (t/n)");
				c = _getch();
				if (c == 't')
				{
					scoreBoard = openScore();
					system("cls");
					b.won = 0;
					setBoard(&b);
					drawBoard(&b);
				}
				else
				{
					printf("%d", _CrtDumpMemoryLeaks());
					return 0;
				}
			}
			if (b.won == 1)
			{
				printf("Gratulacje, zwyciêstwo!");
				endGame(b, scoreBoard);
				printf("\nZagraæ ponownie? (t/n)\n");
				c = _getch();
				if (c == 't')
				{
					scoreBoard = openScore();
					system("cls");
					b.won = 0;
					setBoard(&b);
					drawBoard(&b);
				}
				else
				{
					return 0;
				}

			}
			//printf("q - wyjœcie\nr - reset\n");
		}
	}
}