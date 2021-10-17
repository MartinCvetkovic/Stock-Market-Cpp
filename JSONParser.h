#ifndef _JSONPARSER_H_
#define _JSONPARSER_H_

#include "Parser.h"
#include "Stock.h"
#include <fstream>
#include <regex>
#include "Exceptions.h"
#include <iostream>

using namespace std;

class JSONParser: public Parser {

public:

	virtual void parseFile(Stock* stock);
	virtual double parseCurrentPrice();

};

#endif
