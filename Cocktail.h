#ifndef COCKTAIL_H
#define COCKTAIL_H
#include "BevandaAlcolica.h"
#include <vector>
#include <utility>
#include <string>

class Cocktail: public BevandaAlcolica
{
private:
	std::vector<std::pair<std::string, unsigned int>> ingredienti;
public:
	Cocktail();
	double gradazioneAlcolica() const override;
};

#endif // COCKTAIL_H