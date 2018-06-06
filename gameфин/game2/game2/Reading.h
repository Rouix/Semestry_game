#pragma once
#include "Algorithm.h"

class Reading
{
public:
	void readbaseaction(Algorithm &objAlg);
	void readaction(QFile &file, QTextStream &stream, Algorithm &objAlg,int &point);
	Reading();
	~Reading();
};

