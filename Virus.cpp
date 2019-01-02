#include "Virus.h"
#include <random>
#include <ctime>
#include <typeinfo>

Virus::Virus(int a):
    Microorganism (10, a),
    host(nullptr)
{

}

Virus *Virus::clone() const
{
    return new Virus(*this);
}

bool Virus::isAlive() const
{
    return Microorganism::isAlive() || host != nullptr;
}

void Virus::oneDayPassed()
{
    Microorganism::oneDayPassed();
    mutation(getEnvironmentRadiation());
    takeAHit(1);

    if (host != nullptr)
        hitSomeone(host);

    //how to move around the fact that, if the virus is hosted, at the host death the new viruses must be freed and, most importantly, must be added to the container
}

bool Virus::operator==(const Microorganism &m) const
{
    return typeid(*this) == typeid(m) &&
           host == static_cast<const Virus &>(m).host &&
           Microorganism::operator==(m);
}
