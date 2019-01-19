#ifndef LIQUORE_H
#define LIQUORE_H
#include <string>
#include <list>
#include "BevandaAlcolica.h"

class Liquore: public BevandaAlcolica
{
private:
	double alcool;

	static std::list<std::string> espositore;
public:
	Liquore();
	virtual Liquore *clone() const override;
	virtual bool operator==(const Ordinazione &ck) const override;

	static void arrivo(const std::string &l);
	static bool disponibile(const std::string &l);
	static void esaurimento(const std::string &l);
};

#endif // LIQUORE_H