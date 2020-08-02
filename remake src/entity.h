#pragma once
#include <conio.h>	// for _getch() input
#include <vector>
#include "constants.h"
#include "room.h"
#include "item.h"

class Entity	// The player, all enemies, and items, like equipment and warp tiles are an entity
{
public:
	short x;
	short y;
	short id;
	bool item;
	char sprite;

	short xVel;
	short yVel;

protected:
	std::string name;

public:
	std::string getName() const;
};