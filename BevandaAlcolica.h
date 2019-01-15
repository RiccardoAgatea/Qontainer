#ifndef BEVANDAALCOLICA_H
#define BEVANDAALCOLICA_H
#include "Bevanda.h"

class BevandaAlcolica: public Bevanda
{
public:
    BevandaAlcolica();
    virtual double gradazioneAlcolica() const = 0;
};

#endif // BEVANDAALCOLICA_H