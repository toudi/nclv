#ifndef NCLVLISTVIEW_H
#define NCLVLISTVIEW_H

#include "nclvcolumn.h"

class nclvListView
{
public:
	void addColumn(nclvColumn* c);
	void drawBoxes();
	void display();
	void Scroll(int howManyRows);
	void setGeometry(int x, int y, int width, int height);
protected:
	WINDOW* _display;
	std::vector <nclvColumn*> columns;
};

#endif
