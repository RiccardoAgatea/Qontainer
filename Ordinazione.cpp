#include "Ordinazione.h"

Ordinazione::Ordinazione(unsigned int t, unsigned int c, const std::string &n):
	n_tavolo(t),
	n_cameriere(c),
	nome(n)
{

}

bool Ordinazione::operator==(const Ordinazione &mi)
{
	return nome == mi.nome;
}

bool Ordinazione::operator!=(const Ordinazione &mi) const
{
	return !(*this == mi);
}
