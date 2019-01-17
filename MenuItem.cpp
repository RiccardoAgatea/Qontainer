#include "MenuItem.h"

MenuItem::MenuItem(const std::string &n, const std::string &i):
	nome(n),
	immagine(i)
{

}

bool MenuItem::operator==(const MenuItem &mi)
{
	return nome == mi.nome;
}
