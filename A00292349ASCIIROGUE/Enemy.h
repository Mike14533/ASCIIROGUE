#pragma once
#include<string>
class Enemy
{
public:
	Enemy(std::string name, char tile, int level, int attack, int defense, int health, int xp);
	void setPosition(int x, int y);
	void getPosition(int& x, int& y);
	int attack();
	std::string getName() { return _name; }
	char getTile() { return _tile; }
	char getMove(int playerX, int playerY);
	int takeDamage(int attack);
private:
	std::string _name;
	char _tile;
	int _level;
	int _attack;
	int _defense;
	int _health;
	int _xp;
	int _x;
	int _y;
};