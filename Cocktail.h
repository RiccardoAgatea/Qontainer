#ifndef COCKTAIL_H
#define COCKTAIL_H
#include "BevandaAlcolica.h"
#include <vector>
#include <utility>
#include <string>

class Cocktail: public BevandaAlcolica
{
private:
	std::vector<std::pair<Bevanda *, unsigned int>> ingredienti;
public:
	Cocktail();
	virtual Cocktail *clone() const override;
	virtual double gradazioneAlcolica() const override;
	virtual bool operator==(const Cocktail &ck) const override;
};

#endif // COCKTAIL_H