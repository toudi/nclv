#include <iostream>
#include "nclvlistview.h"

class myApp
{
public:
	myApp();
	int run();
protected:
	nclvListView* lv;
};

myApp::myApp()
{
	std::stringstream s;
	this->lv = new nclvListView();
	lv->setGeometry(0,1,COLS,LINES-1);
	nclvColumn* c1= new nclvColumn(" ");
	nclvColumn* c2 = new nclvColumn("Column 1");
	nclvColumn* c3 = new nclvColumn("Column 2");
	this->lv->addColumn(c1);
	this->lv->addColumn(c2);
	this->lv->addColumn(c3);
	for (int i=0; i < 10; i++)
	{
		s.str("");
		s << "Item                ";
		s << i;
		c1->addItem(new nclvItem("   ", COLOR_RED));
		c2->addItem(new nclvItem(s.str()));
		c3->addItem(new nclvItem(s.str()));
	}
	this->lv->display();
}

int myApp::run()
{
	int ch;
	refresh();
	while((ch = getch()) != KEY_F(10))
	{	switch(ch)
		{	
			case KEY_UP:
				this->lv->Scroll(-1);
				break;
			case KEY_DOWN:
				this->lv->Scroll(1);
				break;	
		}
	}
	return 1;
}

int main(void)
{
	initscr();
	cbreak();
	keypad(stdscr, true);
	curs_set(false);
	noecho();
	start_color();
	init_pair(1,COLOR_WHITE,COLOR_BLUE);
	init_pair(2,COLOR_BLUE,COLOR_WHITE);
	init_pair(3,COLOR_RED,COLOR_WHITE);	
	refresh();	
	myApp* app = new myApp();
	int x = app->run();
	endwin();	
	return x;
}
