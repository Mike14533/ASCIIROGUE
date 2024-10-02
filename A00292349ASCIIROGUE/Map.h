#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
class Map
{
public:
	Map();

	void load(std::string mapName, Player& player);
	void print(Player& player);
	void movePlayer(char input, Player& player);
	char getTile(int x, int y);
	void setTile(int x, int y, char tile);
	void updateEnemies(Player& player);
	void level1(Player& player);

	void level2(Player& player);
	void level3(Player& player);
	void level4(Player& player);
	void processMove(Player& player, int targetX, int targetY);
private:
	void processEnemyMove(Player& player, int enemyIndex, int targetX, int targetY);

	
	


	void battleMonster(Player& player, int targetX, int targetY);

	std::vector <std::string> _mapData;
	std::vector <Enemy> _enemies;
	std::vector <Item> _items;
};

