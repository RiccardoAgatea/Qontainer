#ifndef COCKTAIL_H
#define COCKTAIL_H
#include "BevandaAlcolica.h"
#include <vector>
#include <list>
#include <utility>
#include <string>

class Cocktail: public BevandaAlcolica
{
private:
	std::vector<std::string> ingredienti;

	static std::list<std::string> listino;
public:
	Cocktail();
	virtual Cocktail *clone() const override;
	virtual bool operator==(const Ordinazione &ck) const override;
};

#endif // COCKTAIL_H