#include "aim.h"


Aim::Aim()
{
	name = "";
}


Aim::~Aim()
{
}

QString Aim::getName(){
	return name;
}
int Aim::getnum(){
	return num;
}
void Aim::setnum(int tmp){
	num = tmp;
}
void Aim::setname(QString tmp){
	name = tmp;
}