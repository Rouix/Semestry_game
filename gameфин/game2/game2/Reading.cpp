#include "Reading.h"



Reading::Reading()
{
}


Reading::~Reading()
{
}

void Reading::readbaseaction(Algorithm &objAlg){
	QFile file("loc.txt");
	if (!file.open(QIODevice::ReadOnly)) // ѕровер€ем, возможно ли открыть наш файл дл€ чтени€
		return;
	QTextStream stream(&file);
	QString line = stream.readLine();
	Location tr;
	while (line[0] != '/'){
		if (line[0] != '['){
			tr.setnull();
			tr.setname(line);
			line = stream.readLine();
			if (line[0] == '/'){
				objAlg.setLoc(tr);
			}
		}
		/*if (line[0] == '*'){// *ќписание       ///проверить
			line = line.remove(0, 1);
			tr.setdesc(line);///
			line = stream.readLine();
		}*/
		else {
			int k = 1;
			while (line[0] == '['){
				Location* loc = new Location();
				Action tm;
				QStringList list1 = line.split('|');
				list1[0] = list1[0].remove(0, 1);
				QStringList list2;
				tm.setnumber(k);
				k++;
				tm.setdesc(list1[0]);
				if (list1[1].contains('%')){
					list2 = list1[1].split('%');
					loc->setname(list2[0]);
					loc->setnumber(1);
					tm.createloc();
					tm.setnext_loc(loc);
					tm.setkey(list2[1]);
				}
				else{
					loc->setname(list1[1]);
					loc->setnumber(1);
					tm.createloc();
					tm.setnext_loc(loc);
				}
				tr.settransition_act(tm);
				line = stream.readLine();
			}
			objAlg.setLoc(tr);
		}
	}
}



void Reading::readaction(QFile &file, QTextStream &stream, Algorithm &objAlg,int &point ){
	int seq = point;
	QString line;
	while (seq != 0){
		line = stream.readLine();
		seq--;
	}
	
	line = stream.readLine();
	point++;
	int i;
	bool ok = false;
	Location tmp;
	while (line[0] != '/'){
		if (line[0] == '!'){ //!ѕалата
			line = line.remove(0, 1);
			for (i = 0; i < objAlg.getLoc().size(); i++){
				Location tm = objAlg.getLoc()[i];
				if (tm.getname() == line){
					break;
				}
			}
			tmp = objAlg.getLoc()[i];
			tmp.setuse(true);
			line = stream.readLine();
			point++;
		}
		if (line[0] == '['){//основные действи€ в локации
			QStringList list1 = line.split(':');
			list1[0] = list1[0].remove(0, 1);
			Action act;
			if (list1[1].contains('%')){
					QStringList list3 = list1[1].split('%');
					act.setdesc(list3[0]);
					act.setkey(list3[1]);
			}
			else{
			
				act.setdesc(list1[1]);
			}
			act.setnumber(list1[0].toInt(&ok, 10));
			act.setto(list1[0].toInt(&ok, 10));
			act.setfrom(list1[0].toInt(&ok, 10));
			tmp.setbaseaction(act);
			line = stream.readLine();
			point++;
		}
		if (line[0] == '@'){ // когда собрали все 3 кусочка газеты
			QStringList list1 = line.split(':');
			Thing tg;
			int i;
			list1[0] = list1[0].remove(0, 1);
			Action* tmp4 = new Action();
			tmp4->setfrom(list1[0].toInt(&ok, 10));
			if (list1[1].contains('$')){//удалить цель
				QStringList list4 = list1[1].split('$');
				tmp4->setdesc(list4[0]);
				tmp4->setdelaim(list4[1].toInt(&ok, 10));
			}
		
			for (i = 0; i < objAlg.gethero().getinventory().getthings().size(); i++){
				if (objAlg.gethero().getinventory().getthings()[i].getName() == "newspaper"){
					tg = objAlg.gethero().getinventory().getthings()[i];
					tg.setoutact(tmp4);
					break;
				}
			}
			objAlg.addthinginhero(tg);
			line = stream.readLine();
			point++;
		
		}
		if (line[0] == '*'){// *ќписание
			line = line.remove(0, 1);
			tmp.setdesc(line);///
			line = stream.readLine();
			point++;
		}
		if (line[0] == '^'){// *цель
			QStringList list1 = line.split(':');
			Aim tmpaim;
			tmpaim.setname(list1[1]);
			list1[0] = list1[0].remove(0, 1);
			tmpaim.setnum(list1[0].toInt(&ok, 10));
			objAlg.settarget(tmpaim); //записали цель
			line = stream.readLine();
			point++;
		}
		if (line[0] == '?'){//переходы
			Action tmp1;
			bool mainact = false;
			QStringList list1;
			if (line.contains(':')){
				list1 = line.split(':');
				list1[0] = list1[0].remove(0, 1);
				mainact = true;
				tmp1.setdesc(list1[1]);
			}
			if (line.contains('[')){
				list1 = line.split('[');
				list1[0] = list1[0].remove(0, 1);
				if (line.contains('{')){
					QStringList list2 = list1[1].split('{');
					tmp1.setdesc(list2[0]);
					Thing* sub = new Thing();
					sub->setName(list2[1]);
					tmp1.creatething();
					tmp1.setthing(sub);
					
				}
				else{ tmp1.setdesc(list1[1]); }
			}
			bool end = false;
			if (list1[1].contains('~')){//если конец игры
				tmp1.setendgame(true);
				QStringList list4 = list1[1].split('~');
				tmp1.setdesc(list4[0]);
				end = true;
			}
			QVector <Location> locs = objAlg.getLoc();
			objAlg.clearlocations();
			for (int i = 0; i<locs.size(); i++){
				Location tr = locs[i];
				QString tt = tr.getname();
				if (tt.size() == list1[0].size()){
					Location locss = locs[i];
					if (end){
						locss.setreactenter(tmp1);
					}
					if (!end){
						locss.setbaseaction(tmp1);
					}
					else {
					locss.settransition_act(tmp1);
					}
					for (int f = 0; f < locs.size(); f++){
						if (locs[f].getname() == locss.getname()){
							locs.erase(locs.begin() + f);
							break;
						}
					}
					locs.push_back(locss);
					break;
				}
			}
			for (int g = 0; g < locs.size(); g++){
				objAlg.setLoc(locs[g]);
			}
			line = stream.readLine();
			point++;
		}

		if (line[0] >= 48 && line[0] <= 58){
			bool enter = false;
			if (line[1] == '&' || line[2] == '&'){ //1&2:„то происходит?
				Action tmp4;
				QStringList list1 = line.split(':');
				QStringList list2 = list1[0].split('&');
				if (list1[1].contains('{')){//если юзер берет предмет
					Thing* tmpt = new Thing;
					QStringList list3 = list1[1].split('{');
					tmp4.setdesc(list3[0]);
					tmpt->setName(list3[1]);
					tmp4.creatething();
					tmp4.setthing(tmpt);
					enter = true;
					
				}
				if (list1[1].contains('~')){//если конец игры
					tmp4.setendgame(true);
					QStringList list4 = list1[1].split('~');
					tmp4.setdesc(list4[0]);
					enter = true;
				}
				if (list1[1].contains('#')){ //урон
					bool in = false;
					QStringList list4 = list1[1].split('#');
					QStringList list5;
					tmp4.setdesc(list4[0]);
					if (list4[1].contains('+')){
						list5 = list4[1].split('+');
						tmp4.sethealth(list5[0].toInt(&ok, 10));
						tmp4.setendpart(true);
						in = true;
					}
					if (list4[1].contains('-')){
						list4[1] = list4[1].remove(0, 1);
						int n = list4[1].toInt(&ok, 10);
						n = n - (n * 2);
						tmp4.sethealth(n);
						in = true;
					}
					if (!in){
						tmp4.sethealth(list4[1].toInt(&ok, 10));
					}
					enter = true;
				}
				if (list1[1].contains('+')){//если конец части
					tmp4.setendpart(true);
					QStringList list4 = list1[1].split('+');
					tmp4.setdesc(list4[0]);
					enter = true;
				}
				if (list1[1].contains('$')){//удалить цель
					QStringList list4 = list1[1].split('$');
					tmp4.setdesc(list4[0]);
					tmp4.setdelaim(list4[1].toInt(&ok, 10));
					enter = true;
				}
				if (line.contains('^')){// цель
					QStringList list4 = list1[1].split('^');
					QStringList list5 = list4[1].split(';');
					Aim* tmpaim = new Aim();
					tmpaim->setname(list5[1]);
					tmpaim->setnum(list5[0].toInt(&ok, 10));
					tmp4.createaim();
					tmp4.setnewaim(tmpaim);
					tmp4.setdesc(list4[0]);
					tmp4.setdelaim(0);
					enter = true;
				
				}
				else {
					if (!enter)tmp4.setdesc(list1[1]);
				}
				tmp4.setfrom(list2[0].toInt(&ok, 10));
				tmp4.setto(list2[1].toInt(&ok, 10));
				objAlg.setacthero(tmp4);
				
				line = stream.readLine();
				point++;
				enter = false;
			}
			if (line[1] == ':' || line[2] == ':'){ // 2:— вами произошло несчастьеЕ
				Action tmp2;
				QStringList list1 = line.split(':');
				if (list1[1].contains('$')){//удалить цель
					QStringList list4 = list1[1].split('$');
					tmp2.setdesc(list4[0]);
					tmp2.setdelaim(list4[1].toInt(&ok, 10));
					enter = true;
				}
				if (list1[1].contains('~')){//если конец игры
					tmp2.setendgame(true);
					QStringList list4 = list1[1].split('~');///////////////////////////////////////
					tmp2.setdesc(list4[0]);
					enter = true;
				}
				if (list1[1].contains('+')){//если конец части
					tmp2.setendpart(true);
					QStringList list4 = list1[1].split('+');///////////////////////////////////////////
					tmp2.setdesc(list4[0]);
					enter = true;
				}
				if (line.contains('^')){// цель
					QStringList list4 = list1[1].split('^');
					QStringList list5 = list4[1].split(';');
					Aim* tmpaim = new Aim();
					tmpaim->setname(list5[1]);
					tmpaim->setnum(list5[0].toInt(&ok, 10));
					tmp2.createaim();
					tmp2.setnewaim(tmpaim);
					tmp2.setdesc(list4[0]);
					tmp2.setdelaim(0);
					enter = true;
					
				}
				if (list1[1].contains('#')){ //урон
					bool in = false;
					QStringList list4 = list1[1].split('#');
					QStringList list5;
					tmp2.setdesc(list4[0]);
					if (list4[1].contains('+')){
						list5 = list4[1].split('+');
						tmp2.sethealth(list5[0].toInt(&ok, 10));
						tmp2.setendpart(true);
						in = true;
					}
					if (list4[1].contains('-')){
						list4[1] = list4[1].remove(0, 1);
						int n = list4[1].toInt(&ok, 10);
						n = n - (n * 2);
						tmp2.sethealth(n);
						in = true;
					}
					if (!in){
						tmp2.sethealth(list4[1].toInt(&ok, 10));
					}
					enter = true;
				}
				else{
					if (!enter)
						tmp2.setdesc(list1[1]);
				}
				tmp2.setnumber(list1[0].toInt(&ok, 10));
				tmp.setaction(tmp2);////////////////////
				line = stream.readLine();
				point++;
				enter = false;
			}
			if (line[1] == '*' || line[2] == '*'){//загадка
				Action tmp3;
				Puzzle* tmpp = new Puzzle();
				QStringList list1 = line.split(':');
				QStringList list2 = list1[0].split('*');
				QStringList list3 = list1[1].split('[');
				tmp3.setfrom(list2[0].toInt(&ok, 10));
				tmp3.setto(list2[1].toInt(&ok, 10));
				tmpp->setdesc(list3[0]);
				tmpp->setans(list3[1]);
				tmp3.createpuz();
				tmp3.setpuzzle(tmpp);
				tmp.setaction(tmp3);
				line = stream.readLine();
				point++;
				
			}
		}
		tmp.setuse(true);
		objAlg.changeloc(tmp, i);
	}
}