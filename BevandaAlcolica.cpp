#include "BevandaAlcolica.h"

BevandaAlcolica::BevandaAlcolica()
{

}

bool BevandaAlcolica::operator==(const Ordinazione &ck) const
{
	return &ck - 1;
}
