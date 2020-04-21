#ifndef OTHERGAME_HPP
#define OTHERGAME_HPP

#define array_size(array) = (sizeof(array) / sizeof((array)[0]))

#include "boxle.hpp"

typedef struct Button{
	int pressed;
	unsigned int x, y;
	unsigned int id;
}Button;

typedef struct Tp{
	int x;
	int y;
	int tx;
	int ty;
	bool linked;
}Tp;

void linkTp(Tp tp1, Tp tp2);
int toggleButton(Level l, Button b[], int array_size);
void toggleDoors(int id, Level level);

void worldMove(Level* level, Player* player, unsigned int dir);
#endif
