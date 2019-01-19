#ifndef CIBO_H
#define CIBO_H


class Cibo
{
private:
	std::string nome;
	std::string immagine;
public:
	explicit Cibo(const std::string &n, const std::string &i = "");
	virtual ~Cibo() = default;
	virtual Cibo *clone() const = 0;
	virtual bool operator==(const Cibo &mi) const;
	bool operator!=(const Cibo &mi) const;
};

#endif // CIBO_H