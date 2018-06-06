#include "game.h"

game::game(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	readactloc();
	int i = 0;
}

game::~game()
{

}
