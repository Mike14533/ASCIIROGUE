#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include <string>
class GameSystem
{
public:
	GameSystem(std::string lvlFile);

	void playGame(Player& player);
	void playerMove();
private:
	Map _map;
	Player _player;
	
};