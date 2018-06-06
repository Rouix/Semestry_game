#pragma once
#include <aim.h>
#include <QtWidgets/QMainWindow>
#include <QString>
#include <QPixmap>
#include <QVector>
#include <QStateMachine>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
class Action;
class Thing
{
	QString name;
	bool use;
	Action* outact;
public:
	QString getName();
	void setName(QString);
	bool getUse();
	void setUse(bool);
	void setoutact(Action* tmp);
	Action* getoutact();
	Thing();
	~Thing();
};

