#include "nclvcolumn.h"

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string/*, chtype color*/)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
//	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
//	wattroff(win, color);
//	refresh();
}

nclvColumn::nclvColumn(std::string desc) 
{ 
	this->description = desc;
	this->legendBoxReady = false;
	this->dataBoxReady = false;
	this->maxItemLength = 0;
	this->currentRow = 0;
}

void nclvColumn::displayLegend(WINDOW* listBoxWindow, int& x)
{
	getmaxyx(listBoxWindow, this->sizeLeftY, this->sizeLeftX);
	this->legendBox = derwin(listBoxWindow, 3, this->maxItemLength+2, 1, x);
	box(this->legendBox, 0, 0);
	print_in_middle(this->legendBox, 1, 0, this->maxItemLength+2, (char*)this->description.c_str());
	this->sizeLeftY-=3;
	this->legendBoxReady = true;
}

void nclvColumn::displayDataBox(WINDOW* listBoxWindow, int& x)
{
	this->dataBox = derwin(listBoxWindow, this->sizeLeftY-2, this->maxItemLength+2, 4, x);
	//box(this->dataBox, 0, 0);
	//wbkgd(this->dataBox,COLOR_PAIR(2));
	wrefresh(this->dataBox);
	this->dataBoxReady = true;
	x+=this->maxItemLength+2;	
}

void nclvColumn::Scroll(int i) 
{
	
	if (i >= 0 && this->currentRow+this->displayOffset+i < this->items.size())
	{
		wbkgd(this->dataWindow[this->currentRow],COLOR_PAIR(2));
		wnoutrefresh(this->dataWindow[this->currentRow]);

		if (this->currentRow >= this->maxDisplayedRows-1)
		{
			this->displayOffset+=i;
			this->displayItems();
			this->currentRow = this->maxDisplayedRows-1;
		}
		else
		{
			this->currentRow+=i;
		}
	}
	else if(i < 0 && this->currentRow+this->displayOffset+i >= 0)
	{
		wbkgd(this->dataWindow[this->currentRow],COLOR_PAIR(2));
		wnoutrefresh(this->dataWindow[this->currentRow]);
		if (this->currentRow == 0)
		{
			this->displayOffset+=i;
			this->displayItems();
			this->currentRow = 0;
		}
		else
		{
			this->currentRow+=i;
		}
	}
	//mvwprintw(stdscr, 0, 0, "Current row: %d, max display: %d, offset: %d", this->currentRow, this->maxDisplayedRows, this->displayOffset);					
	this->selectRow();	
}

void nclvColumn::selectRow()
{
	wbkgd(this->dataWindow[this->currentRow],COLOR_PAIR(1));
  wnoutrefresh(this->dataWindow[this->currentRow]);
  doupdate();
}

void nclvColumn::displayItems()
{
	for (int k=0; k < this->maxDisplayedRows; k++)
	{
		if (this->dataWindow.size() < this->maxDisplayedRows)
		{
			this->dataWindow.push_back(derwin(this->dataBox, 1, this->maxItemLength, k, 1));
			wbkgd(this->dataWindow[k], COLOR_PAIR(2));
		}
		//wprintw(this->dataWindow[k], "");
		mvwprintw(this->dataWindow[k], 0,0, "%s", this->clearString.c_str());
		if (k < this->items.size())
		{
			mvwprintw(this->dataWindow[k], 0,0, "%s", this->items[this->displayOffset+k]->getValue());
		}
		wnoutrefresh(this->dataWindow[k]);
	}
}

void nclvColumn::display(WINDOW* listBoxWindow, int& x)
{
	if (!this->legendBoxReady)
		this->displayLegend(listBoxWindow, x);
	if (!this->dataBoxReady)
		this->displayDataBox(listBoxWindow, x);
	int _y, _x;
	getmaxyx(this->dataBox, _y, _x);
	this->clearString = std::string(this->maxItemLength, ' ');
	this->maxDisplayedRows = _y;
	this->displayItems();
	this->Scroll(0);
}

void nclvColumn::addItem(nclvItem* i)
{
	int len = strlen(i->getValue());
	if (len > this->maxItemLength)
		this->maxItemLength = len;
	this->items.push_back(i);
}

