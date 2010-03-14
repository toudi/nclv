#include "nclvlistview.h"

void nclvListView::setGeometry(int x, int y, int width, int height)
{
	this->_display = newwin(height, width, y, x);
	box(this->_display, 0, 0);
}

void nclvListView::addColumn(nclvColumn* c)
{
	this->columns.push_back(c);
}

void nclvListView::Scroll(int howManyRows)
{
	for(int i=0; i < this->columns.size(); i++)
	{
		this->columns[i]->Scroll(howManyRows);
	}
}

void nclvListView::display()
{
	int posx = 1;
	for (int i=0; i < this->columns.size(); i++)
	{
		this->columns[i]->display(this->_display, posx);
	}
	wrefresh(this->_display);	
}
