#include "inventory.h"


Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}

void Inventory::setthing(Thing tmp){
	things.push_back(tmp);
}
QVector <Thing> Inventory::getthings(){
	return things;
}

void Inventory::deletething(Thing tmp){
	for (int i = 0; i < things.size(); i++){
		if (things[i].getName() == tmp.getName()){
			things.erase(things.begin() + i);
		}
	}
}
void Inventory::setuse(int i, bool tmp){
	things[i].setUse(tmp);
}