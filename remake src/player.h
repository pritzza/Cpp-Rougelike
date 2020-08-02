#pragma once
#include "creature.h"

class Player : public Creature
{
private:
	std::vector<Item> inventory;

private:
	int getInput();
	void updateVision(const std::vector<Room>& f, const char m[MAP_HEIGHT][MAP_WIDTH]);

public:
	char vision[MAP_HEIGHT][MAP_WIDTH];

public:
	int tick(Floor& f, std::vector<Entity*>& e, std::vector<Creature*>& c, bool debug);	// debugging
	void tick(Floor& f, std::vector<Entity*>& e, std::vector<Creature*>& c);	// release
	void clearVision();
	void resetPlayer();

	Player(std::vector<Entity*>& e, std::vector<Creature*>& c);
};