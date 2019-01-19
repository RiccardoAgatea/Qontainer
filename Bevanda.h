#ifndef BEVANDA_H
#define BEVANDA_H
#include "Ordinazione.h"

class Bevanda: public Ordinazione
{
public:
	Bevanda();
	virtual Bevanda *clone() const override;
};

#endif // BEVANDA_H