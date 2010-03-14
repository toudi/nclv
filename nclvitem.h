#ifndef NCLVITEM_H
#define NCLVITEM_H

#include <string>

class nclvItem
{
public:
	char* getValue();
	nclvItem(std::string value, int color = -1);
	nclvItem(int value, int color = -1);
	nclvItem(float value, int color = -1);
protected:
	float       flValue;
	int         intValue;
	std::string sValue;
	int type;
};
#endif
