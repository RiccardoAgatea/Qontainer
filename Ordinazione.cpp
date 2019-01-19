#include "Ordinazione.h"

Ordinazione::Ordinazione(unsigned int t, unsigned int c, const std::string &n):
	n_tavolo(t),
	n_cameriere(c),
	cibo(n)
{

}

bool Ordinazione::operator==(const Ordinazione &o) const
{
	return n_tavolo == o.n_tavolo &&
		   n_cameriere == o.n_cameriere &&
		   cibo == o.cibo;
}

bool Ordinazione::operator!=(const Ordinazione &mi) const
{
	return !(*this == mi);
}
