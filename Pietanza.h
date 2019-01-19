#ifndef PIETANZA_H
#define PIETANZA_H
#include "Ordinazione.h"

class Pietanza: public Ordinazione
{
public:
	Pietanza();
	virtual Pietanza *clone() const override;
	virtual bool operator==(const Ordinazione &ck) const override;
};

#endif // PIETANZA_H