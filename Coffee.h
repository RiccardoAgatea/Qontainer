#ifndef COFFEE_H
#define COFFEE_H
#include "Drink.h"

class Coffee: public Drink
{
private:
	std::string notes;

	static const std::string class_name;
	static Order::Empty empty;
public:
	Coffee(unsigned int,
	       const std::string &,
	       unsigned int,
	       const std::string &);
	Coffee *clone() const override;
	std::string getClassName() const override;
	bool isA(const std::string &) const override;
	std::string getNotes() const;
	void setNotes(const std::string &);
	std::vector<std::string> getDetails() const override;
	void setDetails(const std::vector<std::string> &) override;
	bool operator==(const Order &) const override;
};

#endif // COFFEE_H