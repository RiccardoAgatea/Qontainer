#include "Model.h"
#include <QFile>
#include <QSaveFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

Model::Model(const std::string &path)
{
	load(path);
}

void Model::save(const std::string &path) const
{
	QSaveFile file(path.c_str());
}

void Model::load(const std::string &path)
{
	QFile file(path.c_str());
}
