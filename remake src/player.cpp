#include "player.h"

Player::Player(std::vector<Entity*>& e, std::vector<Creature*>& c)
{
	name = "You";
	sprite = '&';
	id = 0;

	e.push_back(this);
	c.push_back(this);
}

void Player::resetPlayer()
{
	clearVision();
	//hp = 10
	//etc
}

void Player::clearVision()
{
	for (int i = 0; i < MAP_WIDTH; i++)
		for (int j = 0; j < MAP_HEIGHT; j++)
			vision[j][i] = ' ';
}

int Player::getInput()
{
	char input;
	input = _getch();

	switch (input)
	{
	case('w'): yVel = -1; break;
	case('s'): yVel = 1; break;
	case('a'): xVel = -1; break;
	case('d'): xVel = 1; break;

	case('r'): return 1; break;	// debug hotkey for floor reset; higher up return value 1 calls progressFloor()
	case(' '):
		if (sight == 1)
			sight = -1;
		else
			sight = 1;
		break;
	}

	return 0;
}

void Player::updateVision(const std::vector<Room>& f, const char m[MAP_HEIGHT][MAP_WIDTH])
{
	// Used to tell direction in terms of x and y
	//short xd = 0;
	//short yd = 0;
	//
	//switch (direction)
	//{
	//case(0):	// North
	//	yd = -1;
	//	break;
	//case(1):	// South
	//	yd = 1;
	//	break;
	//case(2):	// East
	//	xd = -1;
	//	break;
	//case(3):	// West
	//	xd = 1;
	//	break;
	//}

	// reveals rooms when entering
	for (auto& r : f)	// Goes through each room
		if ((x > r.x && x < r.x + r.width) && (y > r.y && y < r.y + r.height))	// checks if player is inside r
			for (int i = r.x; i < r.x + r.width; i++)
				for (int j = r.y; j < r.y + r.height; j++)
				{
					vision[j][i] = m[j][i];	// adds r to vision map
				}
		else
			for (int i = r.x + 1; i < r.x + r.width - 1; i++)
				for (int j = r.y + 1; j < r.y + r.height - 1; j++)
				{
					vision[j][i] = ' '; // if you leave room, empty room
				}

	for (int i = x - sight - 1; i <= x + sight + 1; i++)
		for (int j = y - sight - 1; j <= y + sight + 1; j++)
		{
			// Erases/forgets tiles out of vision
			if (m[j][i] == ':')
				vision[j][i] = ' ';

			// Draws what you can see
			if (i >= x - sight && i <= x + sight)
				if (j >= y - sight && j <= y + sight)
					vision[j][i] = m[j][i];
		}
}

int Player::tick(std::vector<Entity*>& e, std::vector<Creature*>& c, const char m[MAP_HEIGHT][MAP_WIDTH], const std::vector<Room>& r, bool debug)
{
	// returns input inorder to change gamestates in game obj
	int input = getInput();
	move(e, c, m , r[0]);
	updateVision(r, m);

	return input;
}

void Player::tick(std::vector<Entity*>& e, std::vector<Creature*>& c, const char m[MAP_HEIGHT][MAP_WIDTH], const std::vector<Room>& r)
{
	// returns input inorder to change gamestates in game obj
	getInput();
	move(e, c, m, r[0]);
	updateVision(r, m);
}
