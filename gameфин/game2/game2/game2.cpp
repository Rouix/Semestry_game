#include "game2.h"

Game::Game(QWidget *parent)
	: QMainWindow(parent)
{
	Person namePers;
	namePers.setName(putName());

	ui.setupUi(this);
	QPixmap pix("map.jpg");
	ui.label_8->setPixmap(pix);

	showIntro();
	Thing sdd;
	sdd.setName("newspaper");
	sdd.setUse(false);
	objAlg.addthinginhero(sdd);

	ui.label_7->setWordWrap(true);
	ui.label_2->setAlignment(Qt::AlignTop);
	ui.label2->setAlignment(Qt::AlignTop);
	ui.label_6->setAlignment(Qt::AlignTop);
	ui.label_7->setAlignment(Qt::AlignTop);

	mapper = new QSignalMapper(this);
	mapper->setMapping(ui.pushButton, 0);
	mapper->setMapping(ui.pushButton_2, 1);
	mapper->setMapping(ui.pushButton_3, 2);
	mapper->setMapping(ui.pushButton_4, 3);
	mapper->setMapping(ui.pushButton_5, 4);
	
	QObject::connect(ui.pushButton, SIGNAL(clicked()), mapper, SLOT(map()));
	QObject::connect(ui.pushButton_2, SIGNAL(clicked()), mapper, SLOT(map()));
	QObject::connect(ui.pushButton_3, SIGNAL(clicked()), mapper, SLOT(map()));
	QObject::connect(ui.pushButton_4, SIGNAL(clicked()), mapper, SLOT(map()));
	QObject::connect(ui.pushButton_5, SIGNAL(clicked()), mapper, SLOT(map()));

	QObject::connect(mapper, SIGNAL(mapped(int)), this, SLOT(situation(int)));
	ui.pushButton->setText(UTF8(L"Начать игру"));
}

Game::~Game()
{
}

void Game::rewriteact(int num,Action &answer){
	for (int i = 0; i < objAlg.getrightact().size(); i++){
		if (objAlg.getrightact()[i].getnumber() == num){
			answer = objAlg.getrightact()[i];
			if (answer.getnext_loc() == NULL){
				objAlg.rewriteloc(answer);
			}
		}
	}
	Location now = objAlg.getnow_loc();
	objAlg.setnow_loc(now);
	if (answer.getendpart()){
		objAlg.setEndPart(true);
	}
	objAlg.rewritenowloc();
	objAlg.clearrightact();
}
void Game::callAlg(int num,Action &answer,bool &tmp){
	rewriteact(num, answer);
	checkendpart(tmp, answer);
	tmp = objAlg.getEndPart();
	objAlg.algoritm(tmp, answer, this);
}
void Game::situation(int num)
{
	QObject *obj = QObject::sender();
	Action answer;
	answer.setdesc("");
	bool tmp = objAlg.getEndPart();
	callAlg(num,answer,tmp);
	tmp = objAlg.getEndPart();
	if (tmp){
		callAlg(num, answer, tmp);
	}
}

void Game::checkendpart(bool &tmp,Action &answer){
	QFile file("file.txt");
	if (!file.open(QIODevice::ReadOnly)) return;
	QTextStream stream(&file);
	if (tmp){
		int g = objAlg.getpoint();
		if (objAlg.getLoc().size() != 0){
			objAlg.clearlocations();
		}
		objAlg.clearacthero();
		inputText.readbaseaction(objAlg);
		inputText.readaction(file, stream, objAlg, g);
		objAlg.setpoint(g);
		objAlg.setEndPart(false);
		objAlg.setconver(false);
		Location tmm;
		objAlg.setnow_loc(tmm);
		Action tmp;
		answer = tmp;
	}
}

void Game::showIntro()
{
	QMessageBox intro;
	QFile file("main.txt");
	if (!file.open(QIODevice::ReadOnly)) 	return;
	QTextStream stream(&file);
	QString line = stream.readLine();
	intro.setText(line);
	intro.show();
	intro.exec();
}


void  Game::showEndGame(QString desc)
{

	QMessageBox ending;
	ending.setText(desc);
	ending.show();
	ending.exec();
	QCoreApplication::quit();

}


QString Game::putName()
{
	bool ok;
	QString name = QInputDialog::getText(this,
		UTF8(L"Введите своё имя"),
		UTF8(L"Вашe имя:"),
		QLineEdit::Normal,
		QDir::home().dirName(), &ok);

	if (!ok || name.isEmpty())
	{
		QMessageBox error;
		error.setText(UTF8(L"Введите своё имя"));
		error.exec();
		putName();
	}
	return name;
}


QString Game::putAnsPuzzle(Puzzle puz)
{
	bool ok;
	QString yourAnswer = QInputDialog::getText(this,
		UTF8(L"Введите ответ:"), 
		puz.getdesc(),
		QLineEdit::Normal,
		QDir::home().dirName(), &ok);

	if (!ok || yourAnswer.isEmpty() || yourAnswer != puz.getRightAns())
	{
		QMessageBox error;
		error.setText(UTF8(L"Введите верный ответ"));
		error.exec();
		putAnsPuzzle(puz);
	}
	return yourAnswer;
}

QString Game::choicemap(Location &tmp){
	QString tmpline;
	if (tmp.getname() == (UTF8(L"Коридор"))){
		tmpline = "maphall.jpg";
	}
	if (tmp.getname() == (UTF8(L"Общая комната"))){
		tmpline = "maproom.jpg";
	}
	if (tmp.getname() == (UTF8(L"Сад"))){
		tmpline = "mapgarden.jpg";
	}
	if (tmp.getname() == (UTF8(L"Палата"))){
		tmpline = "mapcham.jpg";
	}
	if (tmp.getname() == (UTF8(L"Лаборатория"))){
		tmpline = "maplab.jpg";
	}
	if (tmp.getname() == (UTF8(L"Дом доктора Оливера"))){
		tmpline = "maphouse.jpg";
	}
	return tmpline;
}
void Game::outputLabels(Person mainHero, Location now_loc)
{
	ui.label_9->setText(now_loc.getname());
	ui.label_7->setText(now_loc.getdesc());
	ui.label2->setText(QString::number(mainHero.gethealth()));
	QString things, aims;
	for (int j = 0; j < mainHero.getinventory().getthings().size(); j++)
	{
		if (mainHero.getinventory().getthings()[j].getUse()){
			things += mainHero.getinventory().getthings()[j].getName() + '\n';
		}
	}
	ui.label_2->setText(things);

	for (int j = 0; j < mainHero.getaim().size(); j++)
	{
		aims +=  mainHero.getaim()[j].getName()+ '\n';
	}
	ui.label_6->setText(aims);
	QString line=choicemap(now_loc);
	QPixmap pix(line);
	ui.label_8->setPixmap(pix);
	
}

void Game::outputLabelsAct(Person mainHero, Action now_act)
{
	
	ui.label_7->setText(now_act.getdesc());

}
void Game::showNewspaper(Action go_pic)
{
	QMessageBox pmbx;
	pmbx.setText(go_pic.getdesc());
	QPixmap pix("new.jpg");
	pmbx.setIconPixmap(pix);
	pmbx.show();
	pmbx.exec();
}

int Game::choiceuseact(Location now_loc, QVector <Action>&rightact, QVector <Action>&rightoutput){
	QVector <Action> base = now_loc.getbaseactions();
	QVector <Action> trans = now_loc.gettransition_act();
	QVector <Action> action_loc = now_loc.getactions();
	int base_num = base.size();
	int trans_num = trans.size();
	int action_loc_num = action_loc.size();
	int right_num = rightact.size();
	if (objAlg.getconver()){
		for (int i = 0; i < right_num; i++){
			rightoutput.push_back(rightact[i]);
		}
		return 0;
	}
	if ((right_num == 0) && (action_loc_num == 0) && (base_num == 0)){
		for (int i = 0; i < trans_num; i++){
			objAlg.checkendgame(trans[i]);
			rightoutput.push_back(trans[i]);
		}
		return 0;
	}
	if ((base_num > 0) && (trans_num > 0)){

		for (int i = 0; i < base_num; i++){
			rightoutput.push_back(base[i]);
		}
		for (int i = 0; i < trans_num; i++){
			rightoutput.push_back(trans[i]);
		}
		return 0;
	}
	if (((trans_num > 0) && (action_loc_num>0)) || ((base_num != 0) && (right_num != 0)) || (objAlg.getconver())){
		for (int i = 0; i < right_num; i++){
			objAlg.checkendgame(trans[i]);
			rightoutput.push_back(rightact[i]);
		}
		return 0;

	}
	if (rightoutput.size() == 0){
		if (rightact.size() != 0){
			for (int i = 0; i <rightact.size(); i++){
				rightoutput.push_back(rightact[i]);
			}
		}
	}
		return 0;
}
int Game::outputButton(QVector <Action> rightact, Location now_loc)
{
	int t = 0;
	int it = 0;
	QVector <Action> rightoutput;
	choiceuseact(now_loc, rightact, rightoutput);
	int num_action = 0;//это просто проверка,пока не выполнили все действия в локации
	int num_use = 0;
	int numnullact = 0;
		if (!objAlg.getconver()){
			for (int i = 0; i < objAlg.getLoc().size(); i++){
				if (objAlg.getLoc()[i].getbaseactions().size() != 0){
					numnullact++;
				}
			}
		}
		if (!objAlg.getconver()){
			if (numnullact == 0){
				objAlg.setEndPart(true);
				return 0;
			}
		}
	if (rightoutput.size() > 0)
		{
			ui.pushButton->setText(rightoutput[t].getdesc());

			if (rightoutput.size() > 1)
			{
				t++;
				ui.pushButton_2->setText(rightoutput[t].getdesc());
				ui.pushButton_2->setEnabled(true);

				if (rightoutput.size() > 2)
				{
					t++;
					ui.pushButton_3->setText(rightoutput[t].getdesc());
					ui.pushButton_3->setEnabled(true);
					if (rightoutput.size() > 3)
					{
						t++;
						ui.pushButton_4->setText(rightoutput[t].getdesc());
						ui.pushButton_4->setEnabled(true);
						if (rightoutput.size() > 4)
						{
							t++;
							ui.pushButton_5->setText(rightoutput[t].getdesc());
							ui.pushButton_5->setEnabled(true);
						}
						else{
							ui.pushButton_5->setText("");
							ui.pushButton_5->setEnabled(false);
						}
					}
					else{
						ui.pushButton_4->setText("");
						ui.pushButton_4->setEnabled(false);
						ui.pushButton_5->setText("");
						ui.pushButton_5->setEnabled(false);
					}
				}
				else{
					ui.pushButton_3->setText("");
					ui.pushButton_3->setEnabled(false);
					ui.pushButton_4->setText("");
					ui.pushButton_4->setEnabled(false);
					ui.pushButton_5->setText("");
					ui.pushButton_5->setEnabled(false);
				}
			}
			else
			{
				ui.pushButton_2->setText("");
				ui.pushButton_2->setEnabled(false);
				ui.pushButton_3->setText("");
				ui.pushButton_3->setEnabled(false);
				ui.pushButton_4->setText("");
				ui.pushButton_4->setEnabled(false);
				ui.pushButton_5->setText("");
				ui.pushButton_5->setEnabled(false);
			}
		}
		return 0;
}