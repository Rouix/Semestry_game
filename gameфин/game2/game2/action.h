#pragma once
#include <thing.h>

class Location;
class Thing;
class Puzzle;

class Middle{
	bool use;
	int number;
	QString description;
public:
	void setuse(bool tmp);
	bool getuse();
	void setdesc(QString dec);
	QString getdesc();
	void setnumber(int i);
	int getnumber();
};

class Puzzle :public Middle
{
	QString answer;
	Thing* sub;
	QString yourAnswer;
public:
	Puzzle();
	QString getRightAns();
	void setAnswer(QString);
	void setRightAnswer(QString);
	void setdes(QString tmp);
	void setans(QString tmp);
	void setthing(Thing tmp);
	Thing* getthing();
	~Puzzle();
};

class Action :public Middle
{
	Puzzle* puz;
	int from;
	int to;
	QString key;
	Location* next_loc;
	Thing* subject;
	int delete_aim;
	int health;
	bool end_game;
	bool end_part;
	Aim* new_aim;
public:
	void createpuz();
	void createloc();
	void creatething();
	void createaim();
	void sethealth(int tmp);
	int gethealth();
	void setdelaim(int i);
	int getdelaim();
	void setkey(QString tmp);
	QString getkey();
	void setnext_loc(Location* next);
	Location* getnext_loc();
	void setfrom(int i);
	void setto(int i);
	void setpuzzle(Puzzle* tmp);
	Puzzle* getpuzzle();
	void setthing(Thing* tmp);
	Thing* getthing();
	void setendgame(bool tmp);
	int getfrom();
	int getto();
	void setendpart(bool tmp);
	bool getendgame();
	bool getendpart();
	void setnewaim(Aim* tmp);
	Aim* getnewaim();
	Action();
	~Action();
};

class Location :public Middle
{
	QString name;
	QVector <Action> actions_loc;//разговоры
	QVector <Action> base_actions_loc;//поговорить с китом и так далее
	QVector <Action> transition_act;//переходы по локациям
	Action reactenter;//действие,когда заходишь в локацию
	
public:
	Location();
	void setreactenter(Action tmp);
	Action getreactenter();
	void setname(QString tmp);
	void setusebase(Location &tmp, int i);
	void setnumbaseact(bool tmp, int i);
	void erasebaseact(int i);
	QString getname();
	void cleartransaction_act();
	void settransition_act(Action tmp);
	QVector <Action> gettransition_act();
	void setaction(Action tmp);
	QVector<Action> getactions();
	void setbaseaction(Action tmp);
	QVector<Action> getbaseactions();
	void setnull();
	~Location();
};

