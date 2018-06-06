#ifndef Game_H
#define Game_H

//#define UTF8 QString::fromWCharArray

#include <QtWidgets/QMainWindow>
#include "ui_game2.h"
#include <QString>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QDir> 
#include <iostream>
#include <QSignalMapper>
#include "Reading.h"
#include <QVector>
#include <QInputDialog>
#include <QMessageBox>

class Game : public QMainWindow
{
	Q_OBJECT
private:
	Algorithm objAlg;
	Reading inputText;
public:
	Game(QWidget *parent = 0);
	~Game();
	void checkendpart(bool &tmp, Action &answer);
	void callAlg(int num, Action &answer, bool &tmp);
	void rewriteact(int num, Action &answer);
	int choiceuseact(Location, QVector <Action>&rightact, QVector <Action>&rightoutput);
	void showNewspaper(Action);
	void showIntro();
	void showEndGame(QString);
	QString choicemap(Location &tmp);
	int outputButton(QVector <Action> rightact, Location);
	void outputLabels(Person mainHero, Location now_loc);
	void outputLabelsAct(Person mainHero, Action now_act);
	QString putName();
	QString putAnsPuzzle(Puzzle);
	QSignalMapper *mapper;
	
private slots:
	void situation(int);

private:
	Ui::game2Class ui;
};

#endif // Game_H
