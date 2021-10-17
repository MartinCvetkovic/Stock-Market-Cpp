#ifndef _EMAINDICATOR_H_
#define _EMAINDICATOR_H_

#include "Indicator.h"

class EMAIndicator : public Indicator {

public:

	virtual void calculateIndicator(Stock stock);

};

#endif
