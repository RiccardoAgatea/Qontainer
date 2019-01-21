#ifndef ORDINAZIONE_H
#define ORDINAZIONE_H
#include <string>

class Ordinazione
{
private:
	unsigned int n_tavolo, n_cameriere;
	std::string cibo;
public:
	Ordinazione() = default;
	explicit Ordinazione(unsigned int t, unsigned int c, const std::string &n);
	virtual ~Ordinazione() = default;
	virtual Ordinazione *clone() const = 0;
	virtual bool operator==(const Ordinazione &o) const;
	bool operator!=(const Ordinazione &o) const;
};

#endif // ORDINAZIONE_H