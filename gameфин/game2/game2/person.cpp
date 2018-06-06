#include "person.h"


Person::Person()
{
	health = 100;
}

void Person::setusething(int i, bool tmp){
	Inventories.setuse(i, tmp);
}
Person::~Person()
{
}
void Person::clearact(){
	actions_per.clear();
}
void Person::setthing(Thing tmp){
	Inventories.setthing(tmp);
}
void Person::eraseaim(int i){
	target.erase(target.begin() + i);
}
int Person::gethealth(){
	return health;
}
void Person::changehealth(int i){
	health = health+i;
}

QString Person::getName(){
	return name;
}

void Person::setName(QString tmp){
	name = tmp;
}
Inventory Person::getinventory(){
	return Inventories;
}
void Person::setaim(Aim tmp){
	target.push_back(tmp);
}
QVector <Aim> Person::getaim(){
	return target;
}

QVector <Action> Person::getaction(){
	return  actions_per;
}
void Person::setaction(Action tmp){
	actions_per.push_back(tmp);
}

void Person::takeThing(Thing tmp){
	Inventories.setthing(tmp);
}

void Person::useThing(Thing tmp){
	Inventories.deletething(tmp);
}