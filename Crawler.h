#ifndef _CRAWLER_H_
#define _CRAWLER_H_

#include <iostream>
#include <string>
#define CURL_STATICLIB
#include <curl/curl.h>
#include "Exceptions.h"
#include <fstream>
#include <direct.h>
#include "Stock.h"

using namespace std;

class Crawler {

	long startPeriod = 0, endPeriod = 0;
	string stockSymbol = "";

public:

	void input();
	void setCrawler(string symb, long start, long end);
	void collectData();

	Stock* returnStock();

};

#endif
