#include "Liquore.h"
#include <algorithm>

Liquore::Liquore()
{

}

Liquore *Liquore::clone() const
{
	return new Liquore(*this);
}

void Liquore::arrivo(const std::string &l)
{
	espositore.push_back(l);
}

bool Liquore::disponibile(const std::string &l)
{
	return std::find(espositore.begin(), espositore.end(), l) != espositore.end();
}

void Liquore::esaurimento(const std::string &l)
{
	auto it = std::find(espositore.begin(), espositore.end(), l);

	if (it != espositore.end())
		espositore.erase(it);
}
