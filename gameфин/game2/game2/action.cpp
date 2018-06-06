#include "action.h"

void Middle::setuse(bool tmp){
	use = tmp;
}
bool Middle::getuse(){
	return use;
}
void Middle::setdesc(QString dec){
	description = dec;
}
QString Middle::getdesc(){
	return description;
}
void Middle::setnumber(int i){
	number = i;
}
int Middle::getnumber(){
	return number;
}


Puzzle::Puzzle()
{
	answer = "";
}
void Puzzle::setans(QString tmp){
	answer = tmp;
}
void Puzzle::setthing(Thing tmp){
	sub = &tmp;
}
Thing* Puzzle::getthing(){
	return sub;
}
QString Puzzle::getRightAns()
{
	return answer;
}

void Puzzle::setRightAnswer(QString tmp){
	answer = tmp;
}
void Puzzle::setAnswer(QString tmp){
	yourAnswer = tmp;
}

Puzzle::~Puzzle()
{
}

void Action::sethealth(int tmp){
	health = tmp;
}


int  Action::gethealth(){
	return health;
}
void  Action::setdelaim(int i){
	delete_aim = i;
}
int  Action::getdelaim(){
	return delete_aim;
}
void  Action::setkey(QString tmp){
	key = tmp;
}
QString  Action::getkey(){
	return key;
}
void  Action::setnext_loc(Location* next){
	next_loc = next;
}
Location*  Action::getnext_loc(){
	return next_loc;
}
void  Action::setfrom(int i){
	from = i;
}
void  Action::setto(int i){
	to = i;
}
void  Action::setpuzzle(Puzzle* tmp){
	puz = tmp;
}
Puzzle*  Action::getpuzzle(){
	return puz;
}
void  Action::setthing(Thing* tmp)
{
	subject = tmp;
}
Thing*  Action::getthing(){
	return subject;
}
void  Action::setendgame(bool tmp){
	end_game = tmp;
}
void  Action::setendpart(bool tmp){
	end_part = tmp;
}
bool  Action::getendgame(){
	return end_game;
}
bool  Action::getendpart(){
	return end_part;
}

int Action::getfrom(){
	return from;
}
int Action::getto(){
	return to;
}

void Action::setnewaim(Aim* tmp){
	new_aim = tmp;
}
Aim* Action::getnewaim(){
	return new_aim;
}
Action::Action()
{
	setuse(false);
	end_game = false;
	end_part = false;
	health = 0;
	delete_aim = 0;
	setnumber(0);
	from = 0;
	to = 0;
	puz = NULL;
	next_loc = NULL;
	subject = NULL;
	new_aim = NULL;

}
Action::~Action()//////////////////////////////////////////////////
{
	/*delete puz;
	delete next_loc;
	delete subject;
	delete new_aim;*/
}
void Action::createpuz(){
	puz = new Puzzle();
}
void Action::createloc(){
	next_loc = new Location();
}
void Action::creatething(){
	subject = new Thing();
}
void Action::createaim(){
	new_aim = new Aim();
}
void Location::setname(QString tmp){
	name = tmp;
}
QString Location::getname(){
	return name;
}
Location::Location()
{
	setname("");
	setuse(false);
	setdesc("");
	setnumber(0);

}

void Location::cleartransaction_act(){
	transition_act.clear();
}
void Location::settransition_act(Action tmp){
	transition_act.push_back(tmp);
}
QVector <Action> Location::gettransition_act(){
	return transition_act;
}

void Location::setaction(Action tmp){
	actions_loc.push_back(tmp);
}
QVector<Action> Location::getactions(){
	return actions_loc;
}
void Location::setbaseaction(Action tmp){
	base_actions_loc.push_back(tmp);
}
QVector<Action> Location::getbaseactions(){
	return base_actions_loc;
}
void Location::setnull(){
	this->setname("");
	this->setnumber(0);
	this->setdesc("");
	this->actions_loc.clear();
	this->base_actions_loc.clear();
	this->transition_act.clear();
}
Location::~Location(){};

void Location::setusebase(Location &tmp, int i){
	tmp.base_actions_loc[i].setuse(true);
}
void Location::setnumbaseact(bool tmp, int i){
	base_actions_loc[i].setnumber(tmp);
}
void Location::erasebaseact(int i){
	base_actions_loc.erase(base_actions_loc.begin() + i);
}

void Location::setreactenter(Action tmp){
	reactenter = tmp;
}
Action Location::getreactenter(){
	return reactenter;
}
