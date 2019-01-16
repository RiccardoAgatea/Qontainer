#ifndef MENUITEM_H
#define MENUITEM_H
#include <string>

class MenuItem
{
private:
	std::string nome;
	std::string immagine;
public:
	MenuItem(const std::string &n, const std::string &i = "");
	virtual ~MenuItem() = default;
};

#endif // MENUITEM_H