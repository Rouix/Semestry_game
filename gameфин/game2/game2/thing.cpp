#include "thing.h"


Thing::Thing()
{
		name = "";
		use = false;
}

Thing::~Thing()
{
}

QString Thing::getName(){
	return name;
}

void Thing::setName(QString nam){
	name = nam;
}

bool Thing::getUse() {
	return use;
}

void Thing::setUse(bool tmp){
	use = tmp;
}

void Thing::setoutact(Action* tmp){
	outact = tmp;
}
Action* Thing::getoutact(){
	return outact;
}