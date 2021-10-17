#ifndef _MAINDICATOR_H_
#define _MAINDICATOR_H_

#include "Indicator.h"

class MAIndicator: public Indicator {

public:

	virtual void calculateIndicator(Stock stock);

};

#endif
