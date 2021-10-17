#ifndef _PARSER_H_
#define _PARSER_H_

#include "Stock.h"

class Parser {

public:

	virtual void parseFile(Stock* stock) = 0;
	virtual double parseCurrentPrice() = 0;

};

#endif
