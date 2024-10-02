#pragma once
#include <string>
class Item
{

public:
	Item(int itemId);
	std::string getName();
	std::string getDescription();
	int getAtt();
	int getDef();
	int getId();
	int getPrice();
	
private:
	std::string _name;
	std::string _description;

	int _id;
	int _Att;
	int _Def;
	int _price;
	
};



