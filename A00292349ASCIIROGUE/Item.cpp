#include "Item.h"
#include <string>


Item::Item(int itemId)
{
	
	switch (itemId)
	{
	case 0:
		_name = "Sword";
		_description = "Increase attack by 5 and defense by 1";
		_id = 0;
		_price = 30;

		_Att = 5;
		_Def = 1;

		break;

	case 1:
		_name = "Axe";
		_description = "Increase attack by 6 and defense by 2";
		_id = 1;
		_price = 50;

		_Att = 6;
		_Def = 2;

		break;
	}

}

	int Item::getAtt() {
		return _Att;
	}
	std::string Item::getName() {
		return _name;
	}
	std::string Item::getDescription() {
		return _description;
	}

	int Item::getDef() {
		return _Def;
	}
	int Item::getId() {
		return _id;
	}
	int Item::getPrice() {
		return _price;
	}