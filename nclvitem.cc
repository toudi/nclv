#include "nclvitem.h"

nclvItem::nclvItem(std::string value, int color)
{
	this->sValue = value;
	this->type = 0; //string
}

nclvItem::nclvItem(int value, int color)
{
	this->intValue = value;
	this->type = 1; //int
}

nclvItem::nclvItem(float value, int color)
{
	this->flValue = value;
	this->type = 2; //float
}

char* nclvItem::getValue()
{
	switch(this->type)
	{
		case 0:
		{
			return (char*)this->sValue.c_str();
			break;
		}
	}
}
