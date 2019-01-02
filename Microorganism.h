#ifndef MICROORGANISM_H
#define MICROORGANISM_H

#include <vector>

class Microorganism
{
private:
    unsigned int age{0};
    int life_points, attack;

    static int environment_radiation;
protected:
    void changeLife(int delta);
    void changeAttack(int delta);
public:
    Microorganism(int lp, int a);
    virtual ~Microorganism() = default;
    virtual Microorganism *clone() const = 0;
    virtual bool isAlive() const;
    virtual void takeAHit(int hit);
    virtual void hitSomeone(Microorganism *m) const;
    virtual void oneDayPassed();
    virtual void mutation(int radiation);

    //the comparison operators return true if and only if the two Microorganisms to be compared are of the exact same type and have the same characteristic.
    virtual bool operator==(const Microorganism &m) const;
    bool operator!=(const Microorganism &m) const;

    static int getEnvironmentRadiation();
    static void setEnvironmentRadiation(int value);
};

#endif // MICROORGANISM_H
