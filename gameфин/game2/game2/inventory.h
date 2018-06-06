#pragma once
#include <action.h>
class Inventory
{
	QVector <Thing> things;
public:
	Inventory();
	void setthing(Thing);
	QVector <Thing> getthings();
	void setuse(int i, bool tmp);
	void deletething(Thing);
	~Inventory();
};

