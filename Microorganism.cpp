#include "Microorganism.h"
#include <random>
#include <ctime>


int Microorganism::environment_radiation = 50;

int Microorganism::getEnvironmentRadiation()
{
    return environment_radiation;
}

void Microorganism::setEnvironmentRadiation(int value)
{
    environment_radiation = value;
}

Microorganism::Microorganism(int lp, int a):
    life_points(lp),
    attack(a)
{

}

bool Microorganism::isAlive() const
{
    return life_points > 0;
}

void Microorganism::takeAHit(int hit)
{
    life_points -= hit;
}

void Microorganism::hitSomeone(Microorganism *m) const
{
    m->takeAHit(attack);
}

void Microorganism::oneDayPassed()
{
    ++age;
}

void Microorganism::mutation(int radiation)
{
    std::default_random_engine gen(static_cast<unsigned int>(time(nullptr)));
    std::uniform_real_distribution<int> mutat(1, 100);
    std::uniform_int_distribution<int> coin(0, 1);

    if (mutat(gen) <= radiation)
    {
        int fate = coin(gen) == 0 ? 1 : -1;

        if (coin(gen) == 1)
            life_points += fate * life_points * mutat(gen) / 100;
        else
            attack += fate * attack * mutat(gen) / 100;
    }
}

bool Microorganism::operator==(const Microorganism &m) const
{
    return age == m.age &&
           life_points == m.life_points &&
           attack == m.attack;
}

bool Microorganism::operator!=(const Microorganism &m) const
{
    return !(*this == m);
}
