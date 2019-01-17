#ifndef MENUITEM_H
#define MENUITEM_H
#include <string>

class MenuItem
{
private:
	std::string nome;
	std::string immagine;
public:
	explicit MenuItem(const std::string &n, const std::string &i = "");
	virtual ~MenuItem() = default;
	virtual MenuItem *clone() const = 0;
	virtual bool operator==(const MenuItem &mi);
};

#endif // MENUITEM_H