#include "Player.h"
//#include "Item.h"
#include <random>
#include <ctime>



Player::Player(){
	_x = 0;
	_y = 0;
}

void Player::initialise(int lvl,int gld, int hp, int att, int def, int xp, int room) {
	_lvl = lvl;
	_gld = gld;
	_hp = hp;
	_att = att;
	_def = def;
	_xp = xp;
	_room = room;
	_lvl = 1;
	_gld = 0;
	_hp = 10;
	_att = 4;
	_def = 5;
	_xp = 0;

}

void Player::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

void Player::getPosition(int& x, int& y) {
	x = _x;
	y = _y;
}

int Player::attack() {
	static std::default_random_engine randomEngine(time(NULL));
	std::uniform_int_distribution<int> attackRoll(0, _att);

	return attackRoll(randomEngine);
}

int Player::takeDamage(int attack) {
	

	if (attack > 0) {
		_hp -= attack;

		if (_hp <= 0) {
			return 1;

		}

	}


	return 0;

}

void Player::addExperience(int experience) {

	_xp += experience;

	while (_xp > 50) {
		printf("Leveled up!\n");
		_xp -= 50;
		_att += 10;
		_def += 5;
		_hp += 10;
		_lvl++;


	}
}

void Player::addGold(int gold) {

	_gld += gold;


}
void Player::addToInventory(int Att, int Def) {

	_att += Att;
	_def += Def;

}

void Player::addHealth(int health) {

	_hp == health;


}

//void Player::equipItem(const Item& item) {
//	_item = item;
//}

