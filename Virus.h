#ifndef VIRUS_H
#define VIRUS_H

#include "Microorganism.h"

class Virus : public Microorganism
{
private:
    Microorganism *host;
public:
    Virus(int a);
    virtual ~Virus() override = default;
    virtual Virus *clone() const override;
    virtual bool isAlive() const override;
    virtual void oneDayPassed() override;
    virtual bool operator==(const Microorganism &m) const override;
};

#endif // VIRUS_H
