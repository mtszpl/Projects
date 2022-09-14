#include "funcs.h"

int calculateDistance(const Creature& creatureOne, const Creature& creatureTwo)
{
	int x = (creatureOne.getX() + 10) - (creatureTwo.getY() + 10);
	int y = (creatureOne.getY() + 32) - (creatureTwo.getY() + 32);
	int squared = x * x + y * y;
	return (int) sqrt(squared);
}