#ifndef _INDICATOR_H_
#define _INDICATOR_H_

#include "Stock.h"
#include <vector>
#include "Exceptions.h"

class Indicator {
protected:
	vector<double> result;
	static int interval;

public:

	static void input();

	vector<double> getResult() {
		return result;
	}

	virtual void calculateIndicator(Stock stock) = 0;

};

#endif
