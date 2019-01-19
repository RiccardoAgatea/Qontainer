#include "Pietanza.h"

Pietanza::Pietanza()
{

}

Pietanza *Pietanza::clone() const
{
	return new Pietanza(*this);
}
