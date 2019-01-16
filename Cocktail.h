#ifndef COCKTAIL_H
#define COCKTAIL_H
#include "BevandaAlcolica.h"
#include <vector>
#include <utility>
#include <string>

class Cocktail: public BevandaAlcolica
{
private:
public:
	Cocktail();
	double gradazioneAlcolica() const override;
};

#endif // COCKTAIL_H