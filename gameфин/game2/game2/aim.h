#pragma once
#include <QtWidgets/QMainWindow>
#include <QString>
#include <QPixmap>
#include <QVector>
#include <QStateMachine>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#define UTF8 QString::fromWCharArray
class Aim
{
	int num;
	QString name;
public:
	QString getName();
	int getnum();
	void setnum(int);
	void setname(QString);
	Aim();
	~Aim();
};

