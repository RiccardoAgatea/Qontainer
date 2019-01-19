#ifndef BEVANDAALCOLICA_H
#define BEVANDAALCOLICA_H
#include "Bevanda.h"

class BevandaAlcolica: public Bevanda
{
public:
	BevandaAlcolica();
	virtual BevandaAlcolica *clone() const override = 0;
	virtual bool operator==(const Ordinazione &ck) const override;
};

#endif // BEVANDAALCOLICA_H