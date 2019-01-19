#include "Bevanda.h"

Bevanda::Bevanda()
{

}

Bevanda *Bevanda::clone() const
{
	return new Bevanda(*this);
}
