#include "FanWork.h"

FanWork::FanWork(const Header &h):
    header(new Header(h))
{

}

FanWork::~FanWork()
{
    delete header;
}

const FanWork::Header &FanWork::getHeader() const
{
    return *header;
}

FanWork::Header::Header(const QString &ti, const QString &a, const QString &f,
                        const QVector<QString> &ta):
    title(ti),
    author(a),
    fandom(f),
    tags(ta)
{

}

FanWork::Header::~Header()
{

}

const QString &FanWork::Header::getTitle() const
{
    return title;
}

const QString &FanWork::Header::getAuthor() const
{
    return author;
}

const QString &FanWork::Header::getFandom() const
{
    return fandom;
}

const QDate &FanWork::Header::getPublicationDate() const
{
    return publication_date;
}

const QVector<QString> &FanWork::Header::getTags() const
{
    return tags;
}
