#ifndef RRRR_H
#define RRRR_H

#include <QtWidgets/QMainWindow>
#include "ui_rrrr.h"
#include <person.h>
#include <QFile>
#include <QDebug>
#include <QByteArray>
class game : public QMainWindow
{
	Q_OBJECT
	person mainHero;
	QVector <action>history;
	QVector<location> locations;
	public slots:
	void slotname(QString tmp){
		ui.label->setText(tmp);
	}
public:
	game(QWidget *parent = 0);
	~game();
	void setLoc(location loc){
		locations.push_back(loc);
	}
	void readevents();
	void readactloc(){
		//QString line;
		QFile file("C:/Users/1/Downloads/loc.txt"); // создаем объект класса QFile
		//QByteArray data; // Создаем объект класса QByteArray, куда мы будем считывать данные
		if (!file.open(QIODevice::ReadOnly)) // Проверяем, возможно ли открыть наш файл для чтения
			return; // если это сделать невозможно, то завершаем функцию
		QTextStream stream(&file);
		QString line = stream.readLine();
		location loc;
		while (!stream.atEnd()){
			if (line[0] != '['){
				loc.setnull(loc);
				loc.setname(line);
				line = stream.readLine();
			}
			else {
				int k = 1;
				while (line[0] == '['){
				action tmp;
				QStringList list1 = line.split('|');
				list1[0] = list1[0].remove(0, 1);
				QStringList list2;
				tmp.setnumber(k);
				k++;
				tmp.setdesc(list1[0]);
				if (list1[1].contains('%')){
					list2 = list1[1].split('%');
					tmp.setnext_loc(list2[0]);
					tmp.setkey(list2[1]);
				}
				else{
					tmp.setnext_loc(list1[1]);
				}
				loc.setaction(tmp);
				line = stream.readLine();
			}
				setLoc(loc);
			}
		}
	}
	void showevents();
	void showinventory();
	void showLoc(location tmp);
	void showAims();
	void showhealth();
	void showmap();
private:
	Ui::rrrrClass ui;
};

#endif // RRRR_H
