#pragma once
#include "Item.h"

class Player {

public:
	Player();
	void initialise(int lvl, int gld, int hp, int att, int def, int xp, int room);

	void setPosition(int x, int y);
	void getPosition(int& x, int& y);
	int attack();
	int takeDamage(int attack);
	void addExperience(int experience);
	void addGold(int gold);
	void addHealth(int health);
	void addToInventory(int Att, int Def);
	//void equipItem(const Item& item);

	int _lvl;
	int _gld;
	int _hp;
	int _att;
	int _def;
	int _xp;
	int _room;
	//Item _item;
	int _x;
	int _y;
};