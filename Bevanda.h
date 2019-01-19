#ifndef BEVANDA_H
#define BEVANDA_H
#include "Cibo.h"

class Bevanda: public Cibo
{
public:
	Bevanda();
	virtual Bevanda *clone() const override;
};

#endif // BEVANDA_H