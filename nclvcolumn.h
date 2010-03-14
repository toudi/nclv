#ifndef NCLVCOLUMN_H
#define NCLVCOLUMN_H

#include <ncurses.h>
#include <vector>
#include <string.h>
#include <sstream>
#include "nclvitem.h"

class nclvColumn
{
protected:
	std::string description;
	bool legendBoxReady;
	bool dataBoxReady;
	int maxItemLength;
	WINDOW* legendBox;
	WINDOW* dataBox;
	int sizeLeftX;
	int sizeLeftY;
	void displayLegend(WINDOW* listBoxWindow, int& x);	
	void displayDataBox(WINDOW* listBoxWindow, int& x);
	void displayItems();
	std::vector<nclvItem*> items;
	int displayOffset;
	int currentRow;
	void selectRow();
	std::vector<WINDOW*> dataWindow;
	int maxDisplayedRows;
	std::string clearString;
public:
	nclvColumn(std::string desc);
	void display(WINDOW* listBoxWindow, int& x);
	void addItem(nclvItem* i);
	void Scroll(int i);
};

#endif
