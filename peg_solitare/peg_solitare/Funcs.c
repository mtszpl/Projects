#include <malloc.h>
#include <assert.h>

#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "Funcs.h"
#include "Structs.h"


void setBoard(struct Board* board)
{
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
		{
			if((i > 4 && j > 4) || (i < 2 && j > 4) || (i < 2 && j < 2) || (i > 4 && j < 2))
				board->board[i][j] = '*';
			else
			board->board[i][j] = 'o';
		}
	board->board[3][3] = '.';
	board->pose.x = 3;
	board->pose.y = 3;
	
}

void drawBoard(struct Board* board)
{
	for (int i = 0; i < 7; i++)
	{
		int j = 0;
		int l = 7;
		if (i < 2 || i > 4)
		{
			j += 2;
			l -= 2;
			printf("        ");
		}
		printf("   ");
		for (; j < l; j++)
		{
			if ((board->pose.x == i && board->pose.y == j) && board->isSelected != 1)
				printf("(%c) ", board->board[i][j]);
			else if ((board->pose.x == i && board->pose.y == j) && board->isSelected == 1)
				printf("<%c> ", board->board[i][j]);
			else
				printf(" %c  ", board->board[i][j]);
		}
		printf("\n");
	}
}

void moveLeft(struct Board* board)
{
	int x = board->pose.x;
	int y = board->pose.y;
	if (y == 0 || (y == 2 && (x > 4 || x < 2)))
	{
		board->isSelected = 0;
		return;
	}
	else
	{
		if (board->isSelected == 1)
		{
			if (y >= 2 && board->board[x][y - 2] == '.' && board->board[x][y - 1] == 'o')
			{
				board->board[x][y] = '.';
				board->board[x][y - 1] = '.';
				board->board[x][y - 2] = 'o';
				board->pose.y -= 2;
			}
			board->isSelected = 0;
			return;
		}
		else
			board->pose.y -= 1;
	}
}

void moveRight(struct Board* board)
{
	int x = board->pose.x;
	int y = board->pose.y;
	if (y == 6 || (y == 4 && (x > 4 || x < 2)))
	{
		board->isSelected = 0;
		return;
	}
	else
	{
		if (board->isSelected == 1)
		{
			if (y <= 4 && board->board[x][y + 2] == '.' && board->board[x][y + 1] == 'o')
			{
				board->board[x][y] = '.';
				board->board[x][y + 1] = '.';
				board->board[x][y + 2] = 'o';
				board->pose.y += 2;
			}
			board->isSelected = 0;
			return;
		}
		else
			board->pose.y += 1;
	}
}

void moveUp(struct Board* board)
{
	int x = board->pose.x;
	int y = board->pose.y;
	if (x == 0 || (x == 2 && (y < 2 || y > 4)))
	{
		board->isSelected = 0;
		return;
	}
	else
	{
		if (board->isSelected == 1)
		{
			if (x >= 2 && board->board[x - 2][y] == '.' && board->board[x - 1][y] == 'o')
			{
				board->board[x][y] = '.';
				board->board[x - 1][y] = '.';
				board->board[x - 2][y] = 'o';
				board->pose.x -= 2;
			}
			board->isSelected = 0;
			return;
		}
		else
			board->pose.x -= 1;
	}
}

void moveDown(struct Board* board)
{
	int x = board->pose.x;
	int y = board->pose.y;
	if (x == 6 || (x == 4 && (y < 2 || y > 4)))
	{
		board->isSelected = 0;
		return;
	}
	else
	{
		if (board->isSelected == 1)
		{
			if (x <= 4 && board->board[x+2][y] == '.' && board->board[x + 1][y] == 'o')
			{
				board->board[x][y] = '.';
				board->board[x + 1][y] = '.';
				board->board[x + 2][y] = 'o';
				board->pose.x += 2;
			}
			board->isSelected = 0;
				return;
		}
		else
			board->pose.x += 1;
	}
}

void isWon(struct Board* board)
{
	int counter = 0;
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
		{
			if (board->board[i][j] == 'o')
				counter++;
			if (counter > 1)
				return;
		}
	board->won = 1;
}

void isLost(struct Board* board)
{
	if (board->won == 1)
		return;
	int counter = 0;
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			counter += checkForOptions(board, i, j);
	if (counter == 0)
	{
		board->won = -1;
		return;
	}
}

int checkForOptions(struct Board* board, int x, int y)
{
	int counter = 0;
	if (board->board[x][y] == 'o' &&  board->board[x + 2][y] == '.' && board->board[x + 1][y] == 'o')
		counter++;
	if (board->board[x][y] == 'o' && board->board[x - 2][y] == '.' && board->board[x - 1][y] == 'o')
		counter++;
	if (board->board[x][y] == 'o' && board->board[x][y + 2] == '.' && board->board[x][y + 1] == 'o')
		counter++;
	if (board->board[x][y] == 'o' && board->board[x][y - 2] == '.' && board->board[x][y - 1] == 'o')
		counter++;
	return counter;
}

struct score* openScore()
{
	struct score* scr = NULL;
	FILE* f;
	int i = 0;
	f = fopen("scoreboard.bin", "rb");
	if (f == NULL)
		f = fopen("scoreboard.bin", "wb");
	while ((i = getc(f)) != EOF)
	{
		if (scr == NULL)
		{
			scr = malloc(sizeof(struct score));
			fread(scr->name, sizeof(char), 20, f);
			scr->Next = NULL;
			fread(&scr->pegsLeft, sizeof(int), 1, f);
		}
		else
		{
			struct score* p = scr;
			while (p->Next != NULL)
				p = p->Next;
			p->Next = malloc(sizeof(struct score));
			p = p->Next;
			p->Next = NULL;
			fread(p->name, sizeof(char), 20, f);
			fread(&p->pegsLeft, sizeof(int), 1, f);
		}
	}
	fclose(f);
	return scr;
}

struct score* saveScore(struct score* scr, struct score* nwScore)
{
	struct score* p = scr;
	int i = 0;
	if (p != NULL)
	{
		if (nwScore->pegsLeft < scr->pegsLeft)
		{
			nwScore->Next = scr;
			scr = nwScore;
		}
		else
		{
			while (p->Next != NULL && p->Next->pegsLeft < nwScore->pegsLeft)
				p = p->Next;
			while (p->pegsLeft == nwScore->pegsLeft && i < 20 && p->name[i] < nwScore->name[i])
				i++;
			if (nwScore->pegsLeft < p->pegsLeft)
			{
				nwScore->Next = p;
				p = nwScore;
			}
			else
			{
				nwScore->Next = p->Next;
				p->Next = nwScore;
			}
		}
	}
	else
		scr = nwScore;
	p = scr;
	FILE* f;
	f = fopen("scoreboard.bin", "wb");
	while (p != NULL)
	{
		fwrite(" ", sizeof(char), 1, f);
		fwrite(p->name, sizeof(char), 20, f);
		i = p->pegsLeft;
		fwrite(&i, sizeof(int), 1, f);
		p = p->Next;
	}
	p = NULL;
	fclose(f);
	return scr;
}

void printScore(const struct score* scr)
{
	struct score* p = scr;
	while (p != NULL)
	{
		printf("%s  wynik: %d\n", p->name, p->pegsLeft);
		p = p->Next;
	}
}

void endGame(struct Board b, struct score* scoreBoard)
{
	printf("\npodaj imiê: ");
	struct score* newScore = malloc(sizeof(struct score));
	int l = 0;
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			if (b.board[i][j] == 'o')
				l++;
	newScore->pegsLeft = l;
	scanf("%s", newScore->name);
	fflush(stdin);
	newScore->Next = NULL;
	scoreBoard = saveScore(scoreBoard, newScore);
	printScore(scoreBoard);
	closeScore(scoreBoard);
}

void closeScore(struct score* scr)
{
	if (scr == NULL)
		return;
	else
	{
		struct score* p = scr;
		while (scr != NULL)
		{
			p = scr->Next;
			free(scr);
			scr = p;
		}
		p = NULL;
		scr = NULL;
	}
}