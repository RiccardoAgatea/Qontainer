#ifndef ORDINAZIONE_H
#define ORDINAZIONE_H


class Ordinazione
{
private:
	unsigned int n_tavolo, n_cameriere;
	std::string nome;
public:
	explicit Ordinazione(unsigned int t, unsigned int c, const std::string &n);
	virtual ~Ordinazione() = default;
	virtual Ordinazione *clone() const = 0;
	virtual bool operator==(const Ordinazione &mi) const;
	bool operator!=(const Ordinazione &mi) const;
};

#endif // ORDINAZIONE_H