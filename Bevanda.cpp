#include "Bevanda.h"

Bevanda::Bevanda()
{

}

Bevanda *Bevanda::clone() const
{
	return new Bevanda(*this);
}

bool Bevanda::operator==(const Ordinazione &ck) const
{
	return &ck - 1;
}
