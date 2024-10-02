#include "GameSystem.h"
#include "conio.h"

GameSystem::GameSystem(std::string lvlFile) {
	
	_map.load(lvlFile, _player);
	_map.print(_player);
}

void GameSystem::playGame(Player& player) {
	bool isDone = false;

	while (isDone != true) {
		_map.print(_player);
		playerMove(); 
		_map.updateEnemies(_player);
		
	}

}

void GameSystem::playerMove() {
	char input;
	
	input = _getch();
	_map.movePlayer(input, _player);

}