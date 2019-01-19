#include "Cibo.h"

Cibo::Cibo(const std::string &n, const std::string &i):
	nome(n),
	immagine(i)
{

}

bool Cibo::operator==(const Cibo &mi)
{
	return nome == mi.nome;
}

bool Cibo::operator!=(const Cibo &mi) const
{
	return !(*this == mi);
}
