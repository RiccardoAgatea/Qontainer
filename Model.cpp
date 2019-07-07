#include "Model.h"
#include "UnavailableFile.h"
#include "InvalidFile.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>
#include <QSaveFile>
#include <QDebug>

void Model::save(const QString &path) const
{
	QSaveFile file(path);

	if (!file.open(QIODevice::WriteOnly))
		throw UnavailableFile("File " +
		                      path.toStdString() +
		                      " couldn't be opened");

	QXmlStreamWriter str(&file);
	str.setAutoFormatting(true);

	str.writeStartDocument();
	str.writeStartElement("root");

	str.writeEmptyElement("valid_save");
	str.writeAttribute("application", "Qontainer");

	str.writeStartElement("to_do");

	for (auto &o : to_do)
	{
		str.writeStartElement("order");
		str.writeAttribute("type",
		                   QString::fromStdString(o.getClassName()));
		str.writeAttribute("table",
		                   QString::number(o.getTable()));
		str.writeAttribute("item",
		                   QString::fromStdString(o.getItem()));
		str.writeAttribute("quantity",
		                   QString::number(o.getQuantity()));

		for (const auto &x : o.getDetails())
		{
			str.writeEmptyElement("detail");
			str.writeAttribute("value",
			                   QString::fromStdString(x));
		}

		str.writeEndElement(); //order
	}

	str.writeEndElement(); //to_do

	str.writeStartElement("completed");

	for (auto &o : completed)
	{
		str.writeStartElement("order");
		str.writeAttribute("type",
		                   QString::fromStdString(o.getClassName()));
		str.writeAttribute("table",
		                   QString::number(o.getTable()));
		str.writeAttribute("item",
		                   QString::fromStdString(o.getItem()));
		str.writeAttribute("quantity",
		                   QString::number(o.getQuantity()));

		for (const auto &x : o.getDetails())
		{
			str.writeEmptyElement("detail");
			str.writeAttribute("value",
			                   QString::fromStdString(x));
		}

		str.writeEndElement(); //order
	}

	str.writeEndElement(); //completed

	str.writeEndElement(); //root
	str.writeEndDocument();
	file.commit();
}

void Model::load(const QString &path)
{
	QFile file(path);
	Container<Order> temp_to_do, temp_completed;

	if (!file.open(QIODevice::ReadOnly))
		throw UnavailableFile("File " +
		                      path.toStdString() +
		                      " couldn't be opened");

	QXmlStreamReader str(&file);

	str.readNext(); //start document
	str.readNextStartElement(); //start root
	str.readNextStartElement();

	if (!(str.isStartElement() &&
	        str.name() == "valid_save" &&
	        str.attributes().value("application") == "Qontainer"))
		throw InvalidFile("File " +
		                  path.toStdString() +
		                  " isn't a valid savefile");

	str.skipCurrentElement();

	str.readNextStartElement(); //start to_do

	while (str.readNextStartElement() && str.name() == "order")
	{
		std::string type = str.attributes().
		                   value("type").
		                   toString().
		                   toStdString();

		unsigned int table = str.attributes().
							 value("table").
							 toUInt();

		std::string item = str.attributes().
						   value("item").
						   toString().
						   toStdString();

		unsigned int quantity = str.attributes().
								value("quantity").
								toUInt();

		std::vector<std::string> details;

		while (str.readNextStartElement() &&
				str.name() == "detail")
		{
			details.push_back(str.attributes().
							  value("value").
							  toString().
							  toStdString());
			str.skipCurrentElement();
		}

		temp_to_do.push_back(Order::getMake().at(type)(table,
		                     item,
		                     quantity,
		                     details));
	}

	str.readNextStartElement(); //start completed

	while (str.readNextStartElement() && str.name() == "order")
	{
		std::string type = str.attributes().
						   value("type").
						   toString().
						   toStdString();

		unsigned int table = str.attributes().
							 value("table").
							 toUInt();

		std::string item = str.attributes().
						   value("item").
						   toString().
						   toStdString();

		unsigned int quantity = str.attributes().
								value("quantity").
								toUInt();

		std::vector<std::string> details;

		while (str.readNextStartElement() &&
				str.name() == "detail")
		{
			details.push_back(str.attributes().
							  value("value").
							  toString().
							  toStdString());
			str.skipCurrentElement();
		}

		temp_completed.push_back(Order::getMake().at(type)(table,
								 item,
								 quantity,
								 details));
	}

	file.close();

	to_do = std::move(temp_to_do);
	completed = std::move(temp_completed);
}

Model::Index Model::addOrder(const std::string &type,
                             unsigned int table,
                             const std::string &item,
                             unsigned int quantity,
                             const std::vector<std::string> &details)
{
	to_do.push_back(Order::getMake().at(type)(table, item, quantity,
					details));
	return Index(--to_do.end());
}

void Model::removeOrder(const Model::Index &index)
{
	to_do.erase(index);
}

void Model::completeOrder(const Model::Index &index)
{
	to_do.give(index, completed, completed.cend());
}

std::vector<Model::Index>
Model::searchToDo(const std::function<bool (const Order &)> &pred)
{
	std::vector<Index> aux;

	for (auto it = to_do.begin(); it != to_do.end(); ++it)
		if (pred(*it))
			aux.push_back(it);

	return aux;
}

std::vector<Model::Index>
Model::searchCompleted(const std::function<bool (const Order &)>
                       &pred)
{
	std::vector<Index> aux;

	for (auto it = completed.begin(); it != completed.end(); ++it)
		if (pred(*it))
			aux.push_back(it);

	return aux;
}

std::vector<Model::Index> Model::getUnfinishedOrders()
{
	std::vector<Index> aux;

	for (auto it = to_do.begin(); it != to_do.end(); ++it)
		aux.push_back(it);

	return aux;
}

bool Model::empty() const
{
	return to_do.empty() && completed.empty();
}

