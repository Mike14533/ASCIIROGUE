#include "Map.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include "GameSystem.h"
#include "Item.h"
#include <conio.h>
#include <string>
#include <cstdlib>

int room = 1;

Map::Map() {

}

void Map::load(std::string mapName, Player& player) {
	

	std::ifstream file;

	file.open(mapName);
	if (file.fail()) {
		perror(mapName.c_str());
		system("PAUSE");
		exit(1);
	}

	std::string line;

	while (getline(file, line)) {
		_mapData.push_back(line);
	}

	char tile;
	for (int i = 0; i < _mapData.size(); i++) {
		for (int j = 0; j < _mapData[i].size(); j++) {
			tile = _mapData[i][j];

			switch (tile) {
			case '@':
				player.setPosition(j, i);
				player.initialise(player._lvl, player._gld, player._hp, player._att, player._def, player._xp, room);
				break;
			case 'j':
				_enemies.push_back(Enemy("Jaguar", tile, 1, 1, 1, 1, 1));
				_enemies.back().setPosition(j, i);
					break;
			case 'g':
				_enemies.push_back(Enemy("Goblin", tile, 2, 5, 4, 6, 3));
				_enemies.back().setPosition(j, i);
				break;
			case 's':
				_enemies.push_back(Enemy("Snake", tile, 2, 6, 2, 4, 7));
				_enemies.back().setPosition(j, i);
				break;
			case '?':
				_items.push_back(Item(0));
				
				break;

			}

		}
	}
}



void Map::print(Player &player) {
	system("CLS");
	std::cout << std::flush;
	
	for (int i = 0; i < _mapData.size(); i++)
	{
		printf("%s\n", _mapData[i].c_str());
	}
	printf("\n");
	std::cout << "Level: " << player._lvl << " Gold: " << player._gld<< " HP: " << player._hp <<" ATT: " << player._att << " DEF: " << player._def << " XP: " << player._xp <<std::endl;

}
void Map::movePlayer(char input, Player& player) {
	
	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);
	char moveTile;


	switch (input) {
	case'w':
	case'W':
		processMove(player, playerX, playerY - 1);

		break;
	case's':
	case'S':
		processMove(player, playerX, playerY + 1);
		break;
	case'a':
	case'A':
		processMove(player, playerX - 1, playerY);
		break;
	case'd':
	case'D':
		processMove(player, playerX + 1, playerY);
		break;

	}
}


char Map::getTile(int x, int y) {
	return _mapData[y][x];


}
void Map::setTile(int x, int y, char tile) {
	_mapData[y][x] = tile;
}

void Map::processMove(Player& player, int targetX, int targetY) {       // used for processing the players chosen movement
	int playerX;
	int playerY;
	int level = 1;
	player.getPosition(playerX, playerY);
	char moveTile = getTile(targetX, targetY);


	//GameSystem gameSystem2("Level2.txt");

	bool hasWeapon = false;
	

	switch (moveTile) {
	case('.'):
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	case('*'):
		player.addGold(10);
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	case('?'):
		
		if (hasWeapon == false) {
			player.addToInventory(5, 2);
		}
		hasWeapon = true;
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');  
		break;
	case('^'):
		player.addHealth(player._lvl*10);
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	case('+'):
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '+');
		setTile(targetX, targetY, '@');
		break;
	case('#'):
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '#');
		setTile(targetX, targetY, '@');
		break;
	case'%':
		room += 1;
		if (room == 2) {
			level2(player);
		}
		if (room == 3) {
			level3(player);
		}
		if (room == 4) {
			level4(player);
		}
		

		std::cout << room << std::endl;
		return;


		break;
	case('|'):
		std::cout << "Player hit a wall" << std::endl;
		system("PAUSE");
		break;
	case('-'):
		std::cout << "Player hit a wall" << std::endl;
		system("PAUSE");
		break;
	
	default:
		battleMonster(player, targetX, targetY);
		break;
	}
}

void Map::battleMonster(Player& player, int targetX, int targetY) {
	int enemyX;
	int enemyY;
	int attackRoll;
	int attackResult;
	int playerX;
	int playerY;
	std::string enemyName;

	player.getPosition(playerX, playerY);


	for (int i = 0; i < _enemies.size(); i++) {
		_enemies[i].getPosition(enemyX, enemyY);
		enemyName = _enemies[i].getName();
		if (targetX == enemyX && targetY == enemyY) {
	
			attackRoll = player.attack();
			printf("\nPlayer attacked %s with a hit of: %d\n", enemyName.c_str(), attackRoll);
			attackResult = _enemies[i].takeDamage(attackRoll);
			if (attackResult != 0) {
				setTile(targetX, targetY, '.');
				print(player);
				printf("Monster slain\n");

		_enemies[i] = _enemies.back();
				_enemies.pop_back();
				i--;
			
				system("PAUSE");
				player.addExperience(attackRoll);
				



				return;
			}
	
			attackRoll = _enemies[i].attack();
			printf("%s attacked player with a roll of: %d\n", enemyName.c_str(), attackRoll);

			attackResult = player.takeDamage(attackRoll);

			if (attackResult != 0) {

				setTile(playerX, playerY, 'x');
				printf("Player died!\n");
				print(player);
				level1(player);
				player._lvl = 1;
				player._gld = 0;
				player._hp = 10;
				player._att = 5;
				player._def = 5;
				player._xp = 5;
				player._room = 1;
				room = 1;
				
			

				exit(0);
				return;
			}
			
			system("PAUSE");

			return;
		}

	}


}
	
void Map::updateEnemies(Player& player) {
	char enemyMove;
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;


	player.getPosition(playerX, playerY);
	for (int i = 0; i < _enemies.size(); i++) {
		enemyMove = _enemies[i].getMove(playerX, playerY);
		_enemies[i].getPosition(enemyX, enemyY);

		switch (enemyMove) {
		case 'w':
			processEnemyMove(player, i, enemyX, enemyY - 1);
			break;
		case 'a':
			processEnemyMove(player, i, enemyX - 1, enemyY);
			break;
		case 's':
			processEnemyMove(player, i, enemyX, enemyY + 1);
			break;
		
		case 'd':
			processEnemyMove(player, i, enemyX + 1, enemyY);
			break;

		}
	}
}

void Map::processEnemyMove(Player& player, int enemyIndex, int targetX, int targetY) {
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;

	_enemies[enemyIndex].getPosition(enemyX, enemyY);
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		_enemies[enemyIndex].setPosition(targetX, targetY);
		setTile(enemyX, enemyY, '.');
		setTile(targetX, targetY, _enemies[enemyIndex].getTile());
		break;
	case '@':
		battleMonster(player, enemyX, enemyY);
		break;
	case '#':
		break;
	default:
		break;
	}




}
void Map::level1(Player& player) {
	
	GameSystem gameSystem("Level1.txt");

	


	gameSystem.playGame(player);
}
void Map::level2(Player& player) {

	GameSystem gameSystem("Level2.txt");




	gameSystem.playGame(player);
}

void Map::level3(Player& player) {

	GameSystem gameSystem("Level3.txt");




	gameSystem.playGame(player);
}
void Map::level4(Player& player) {

	GameSystem gameSystem("Level4.txt");




	gameSystem.playGame(player);
}

int main() {  

	Player player;

	
	Map map;
	map.level1(player);
	
	

		
		
	return 0;
	

	



	
}
