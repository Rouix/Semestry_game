#include "Algorithm.h"
#include "game2.h"

Algorithm::Algorithm()
{
	point = 0;
	conver = false;
	end_part = true;
}
void Algorithm::setacthero(Action t){
	mainHero.setaction(t);
}
Person Algorithm::gethero(){
	return mainHero;
}
QVector <Action> Algorithm::getrightact(){
	return rightact;
}
void Algorithm::clearlocations(){
	locations.clear();
}

void Algorithm::changeloc(Location tmp, int i){
	locations[i] = tmp;
}
void Algorithm::setLoc(Location loc)
{
	locations.push_back(loc);
}

QVector <Location>  Algorithm::getLoc()
{
	return locations;
}
Algorithm::~Algorithm()
{
}
int Algorithm::getpoint(){
	return point;
}
void Algorithm::clearacthero(){
	mainHero.clearact();
}
void Algorithm::checkendgame(Action tmp){
	if (tmp.getendgame()){
	}
}
void Algorithm::rewritenowloc(){
	for (int i = 0; i < locations.size(); i++){
		if (locations[i].getname() == now_loc.getname()){
			now_loc = locations[i];
		}
	}
}
void Algorithm::setconver(bool tnp){
	conver = tnp;
}
bool Algorithm::getconver(){
	return conver;
}
void Algorithm::clearrightact(){
	rightact.clear();
}
void Algorithm::setnow_loc(Location tmp){
	now_loc = tmp;
}
void Algorithm::settarget(Aim tmp){
	mainHero.setaim(tmp);
}
void Algorithm::setusebaseact(Location &tmp, int i){
	tmp.setusebase(tmp, i);
}
void Algorithm::rewriteloc(Action ans){
	int numloc = 0;
	for (int i = 0; i < locations.size(); i++){
		for (int j = 0; j < locations[i].getbaseactions().size(); j++){
			if (ans.getdesc() == locations[i].getbaseactions()[j].getdesc()){
				locations[i].erasebaseact(j);
				numloc = i;
				break;
			}
		}
	}
	int g = 0;
	for (int k = 0; k < locations[numloc].getbaseactions().size(); k++){
		locations[numloc].setnumbaseact(true, g);
		g++;
	}
}
Location Algorithm::getnow_loc(){
	return now_loc;
}
void Algorithm::checkkey(bool &right, Action now_act){
	QString keys = now_act.getkey();
	for (int t = 0; t < mainHero.getinventory().getthings().size(); t++){
		QString thingname = mainHero.getinventory().getthings()[t].getName();
		if (keys == thingname){
			right = true;
		}
	}
	if (!right){
		//здесь вывод меседжбокса в котором написано:Простите но у вас нет...и тут выводишь keys,который выше
	}
}
void Algorithm::checkaction(Action &now_action, bool &end_game, bool &end_part, bool &key, bool &puz, Game *out)
{
	now_action.setuse(true);
	if (now_action.getnewaim() != NULL){
		Aim tmpaip = *now_action.getnewaim();
		if (tmpaip.getName() != ""){//если есть цель
			Aim tmp = *now_action.getnewaim();
			mainHero.setaim(tmp);
		}
	}
	if (now_action.getkey() != ""){//если надо ключ
		key = true;
	}
	if (now_action.getpuzzle() != NULL){
		Puzzle tmppuz = *now_action.getpuzzle();
		if (tmppuz.getdesc() != ""){//если есть пазл
			puz = true;
		}
	}
	if (now_action.getdelaim()){//надо удалить цель
		for (int i = 0; i < mainHero.getaim().size(); i++){
			int num = mainHero.getaim()[i].getnum();
			int delaim = now_action.getdelaim();
			if (num == delaim){
				mainHero.eraseaim(i);
				break;
			}
		}
	}
	if (now_action.gethealth() != 0){//жизнь
		mainHero.changehealth(now_action.gethealth());
	}
	if (now_action.getendpart() == true){//конец части
		end_part = true;
	}
	if (now_action.getthing() != NULL){
		Thing tmpth = *now_action.getthing();
		if (tmpth.getName() != ""){
			tmpth.setUse(true);
			mainHero.setthing(tmpth);//устанавливаем инвентарь
		}
	}
	if (now_action.getendgame()){//конец игры
		out->showEndGame(now_action.getdesc());
	}
}

void Algorithm::outputlocation(Location &next,Action &answer,Action &now_act, bool &end_game, bool &key, bool &puz,  Game *out){

	int num_loc_act = now_loc.getbaseactions().size();
	int num_tr = now_loc.gettransition_act().size();
	if (!getconver()){
		if (now_act.getto() == 0){
			if (num_loc_act != 0 || num_tr != 0){
				if (next.getname() != ""){
					now_loc = next;
					out->outputLabels(mainHero, now_loc);
					Location tn;
					next = tn;
				}
				out->outputButton(rightact, now_loc);

				int iter = rightact.size();
				for (int f = 0; f < now_loc.getbaseactions().size(); f++){
					Action tmp = now_loc.getbaseactions()[f];
					tmp.setnumber(iter);
					iter++;
					rightact.push_back(tmp);
				}
				for (int f = 0; f < now_loc.gettransition_act().size(); f++){
					Action tmp = now_loc.gettransition_act()[f];
					tmp.setnumber(iter);
					iter++;
					rightact.push_back(tmp);
				}
			}
		}
	}
	//если просто разговор///////////////////////////////////////////////////
	else{
		if (answer.getdesc() == ""){
			for (int i = 0; i < now_loc.getactions().size(); i++){
				int num = now_loc.getactions()[i].getnumber();
				if (num == 1){
					now_act = now_loc.getactions()[i];
				}
			}
		checkaction(now_act, end_game, end_part, key, puz, out);
		}
		out->outputLabels(mainHero, now_loc);
		out->outputLabelsAct(mainHero, now_act);
		int it = 0;
		for (int i = 0; i < mainHero.getaction().size(); i++){
			Action tmp = mainHero.getaction()[i];
			int num_act_hero = tmp.getfrom();
			int num_act = now_act.getnumber();
			if (num_act_hero == num_act){
				tmp.setnumber(it);
				it++;
				rightact.push_back(tmp);
			}
		}
		out->outputButton(rightact,now_loc);
	}
}

void Algorithm::setEndPart(bool tmp)
{
	end_part = tmp;
}
bool Algorithm::getEndPart()
{
	return end_part;
}
void Algorithm::setpoint(int tmp){
	point = tmp;
}
void  Algorithm::addthinginhero(Thing tmp){
	mainHero.takeThing(tmp);
}
int Algorithm::algoritm(bool &end_part, Action &answer, Game* out)
{

	bool end_game = false, key = false, puz = false;
	bool ans_on_news = false, in_loc = false;
	bool in_puz = false, rightkey = false;
	Location next;
	Action now_act;
	setconver(false);
	if (answer.getfrom() != 0 || answer.getto() != 0){
		setconver(true);
	}
	if (answer.getfrom() != 0 && answer.getto() == 0){
		setconver(false);
	}
	if (answer.getdesc() == ""){
		for (int i = 0; i < getLoc().size(); i++){//нашли начальную локацию
			if (getLoc()[i].getuse() == true){
				now_loc = getLoc()[i];
			}
		}
		setconver(false);
		if ((getnow_loc().getactions().size() != 0) && (getnow_loc().getbaseactions().size() == 0)){
			setconver(true);
		}
		out->outputLabels(mainHero, now_loc);
		outputlocation(next, answer, now_act, end_game, key, puz, out);
		in_loc = true;
	}
	checkaction(answer, end_game, end_part, key, puz, out);////////////////проверкааа
	puz = false;
	if (end_part){
		Action tmp;
		answer = tmp;
		return 0;
	}
	if (key)
	{
		checkkey(rightkey,answer);
		if (!rightkey) return 0;
	}
	if (answer.getnext_loc() != NULL){
		QString tline = answer.getnext_loc()->getname();
		if (tline != ""){
			for (int q = 0; q < getLoc().size(); q++){
				if (tline == getLoc()[q].getname()){
					next = getLoc()[q];
				}
			}
			if (next.getreactenter().getdesc()!=""){
				out->showEndGame(next.getreactenter().getdesc());
			}
			Action tmp;
			answer = tmp;
			outputlocation(next, answer, now_act, end_game, key, puz, out);
			in_loc = true;
		}
	}
	else{
		int num_piece = 0;
		int num_news = 0;
		for (int i = 0; i < mainHero.getinventory().getthings().size(); i++){
			if (mainHero.getinventory().getthings()[i].getUse()){
				if (mainHero.getinventory().getthings()[i].getName() == (UTF8(L"отрывок"))){
					num_piece++;
				}
			}
			if (mainHero.getinventory().getthings()[i].getName() == "newspaper"){
				num_news = i;
			}
		}
		if (num_piece == 3){
			Thing tmp = mainHero.getinventory().getthings()[num_news];
			Action go_pic = *tmp.getoutact();
			checkaction(go_pic, end_game, end_part, key, puz, out);
			ans_on_news = true;
			out->showNewspaper(go_pic);
			int to = go_pic.getfrom();
			for (int t = 0; t < mainHero.getaction().size(); t++){////ищем следующий экшн c загадкой
				int locnum = mainHero.getaction()[t].getfrom();
				if (locnum == to){
					now_act = mainHero.getaction()[t];
					in_puz = true;
					rightact.push_back(now_act);
				}
			}
			setconver(true);
			out->outputLabels(mainHero, now_loc);
			out->outputButton(rightact, now_loc);
			setconver(false);
			for (int i = 0; i < mainHero.getinventory().getthings().size(); i++){
				QString tmp = mainHero.getinventory().getthings()[i].getName();
				if (tmp == (UTF8(L"отрывок"))){
					mainHero.setusething(i, false);
				}
				if (tmp == "newspaper"){
					mainHero.setusething(i, false);
				}
			}
		}
		if (ans_on_news){
			Thing news = mainHero.getinventory().getthings()[num_news];
			now_act = *news.getoutact();
		}
		else{
			int to = answer.getto();
			if (to != 0){
				for (int t = 0; t < now_loc.getactions().size(); t++){////ищем следующий экшн
					int locnum = now_loc.getactions()[t].getnumber();
					if (locnum == to){
						now_act = now_loc.getactions()[t];
					}
				}
				if (now_act.getdesc() == ""){
					for (int t = 0; t < now_loc.getactions().size(); t++){////для загадки
						int locnum = now_loc.getactions()[t].getfrom();
						if (locnum == to){
							now_act = now_loc.getactions()[t];
							in_puz = true;
						}
					}
				}
				if (!in_puz){
					int num = now_act.getnumber();
					now_act.setto(num);
					now_act.setfrom(num);
				}
				in_puz = false;
				if (now_act.getdesc() != "" || now_act.getpuzzle() != NULL){
					checkaction(now_act, end_game, end_part, key, puz, out);////////////////проверкааа
					if (puz){//если есть пазл
						Puzzle pp = *now_act.getpuzzle();
						pp.setdesc(pp.getdesc());
						pp.setRightAnswer(pp.getRightAns());
						out->putAnsPuzzle(pp);
						in_puz = true;
						if (now_act.getto() != 0){
							int actnum = now_act.getto();
							for (int t = 0; t < mainHero.getaction().size(); t++){
								int locnum = mainHero.getaction()[t].getfrom();
								if (locnum == actnum){
									Action tmp = mainHero.getaction()[t];
									answer = tmp;
									now_act.setdesc(UTF8(L"Ты уверен?"));
									rightact.push_back(answer);
								}
							}
						}
					}
					puz = false;
					if (end_part) return 0;
					if (key){
						checkkey(rightkey, now_act);
						if (!rightkey) return 0;
					}
				}
			}
			if (!in_puz){
				out->outputLabels(mainHero, now_loc);
			}
			if (!in_loc){
				outputlocation(next, answer, now_act, end_game, key, puz, out);
			}
		}
	}
}