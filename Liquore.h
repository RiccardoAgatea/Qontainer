#ifndef LIQUORE_H
#define LIQUORE_H
#include "BevandaAlcolica.h"

class Liquore: public BevandaAlcolica
{
private:
	double alcool;
public:
	Liquore();
	double gradazioneAlcolica() const override;
};

#endif // LIQUORE_H