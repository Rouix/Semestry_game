#pragma once
#include "person.h"
class Game;

class Algorithm 
{
	Person mainHero;
	QVector <Location> locations;
	QVector <Action> rightact;
	bool end_part;
	bool conver;
	Location now_loc;
	int point;
public:
	void clearacthero();
	void addthinginhero(Thing tmp);
	void checkendgame(Action tmp);//
	void checkkey(bool &right, Action now_act);//
	void rewritenowloc();//
	void setconver(bool tnp);
	bool getconver();
	void clearrightact();
	void setnow_loc(Location tmp);
	void settarget(Aim tmp);
	void setusebaseact(Location &tmp, int i);
	void rewriteloc(Action ans);//
	Location getnow_loc();
	int getpoint();
	void setpoint(int);
	Algorithm();
	QVector <Location> getLoc();
	void clearlocations();//
	void setacthero(Action);
	void changeloc(Location tmp, int i);//
	void setLoc(Location);
	void setEndPart(bool);
	bool getEndPart();
	Person gethero();
	QVector <Action> getrightact();
	void checkaction(Action &now_action, bool &end_game, bool &end_part, bool &key, bool &puz, Game *out);//
	int algoritm(bool &end_part, Action &answer,  Game* out);//
	void outputlocation(Location &next, Action &answer, Action &now_act, bool &end_game, bool &key, bool &puz, Game* out);//
	~Algorithm();
};

