#include "Model.h"
#include <QFile>
#include <QSaveFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "UnavailableFile.h"

Model::Model(const QString &path)
{
	load(path);
}

void Model::save(const QString &path) const
{
	QSaveFile file(path);

	if (!file.open(QIODevice::WriteOnly))
		throw UnavailableFile("Could not open file at path " + path.toStdString());

	QXmlStreamWriter xml(&file);

	xml.setAutoFormatting(true);

	xml.writeStartDocument();

	xml.writeStartElement("root");

	xml.writeStartElement("todo");

	for (auto it = to_do.begin(); it != to_do.end(); ++it)
	{

	}


	xml.writeEndElement();
	xml.writeStartElement("completed");

	for (auto it = completed.begin(); it != completed.end(); ++it)
	{

	}

	xml.writeEndElement();
	xml.writeEndDocument();
}

void Model::load(const QString &path)
{
	QFile file(path);

	if (!file.open(QIODevice::WriteOnly))
		throw UnavailableFile("Could not open file at path " + path.toStdString());
}
