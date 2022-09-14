#pragma once

struct CursorPose
{
	int x;
	int y;
};

struct Board
{
	char board[7][7];
	int isSelected;
	struct CursorPose pose;
	int won;
};

struct score
{
	struct score* Next;
	char name[20];
	int pegsLeft;
};