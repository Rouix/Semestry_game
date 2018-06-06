#pragma once
#include <inventory.h>

class Person
{
	QString name;
	QVector <Action> actions_per;
	Inventory Inventories;
	int health;
	QVector<Aim> target;
public:
	void setusething(int i, bool tmp);
	void clearact();
	void setthing(Thing tmp);
	void eraseaim(int i);
	int gethealth();
	void changehealth(int);
	Inventory getinventory();
	void setaim(Aim tmp);
	QVector <Aim> getaim();
	QVector <Action> getaction();
	QString getName();
	void setName(QString);
	void setaction(Action);
	void takeThing(Thing tmp);
	void useThing(Thing tmp);
	Person();
	~Person();
};

