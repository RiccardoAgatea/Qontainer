#include "FanWork.h"

FanWork::FanWork(const QString &ti, const QString &a, const QVector<QString> &ta):
    header(new Header(ti, a, ta))
{

}

FanWork::~FanWork()
{
    delete header;
}

const FanWork::Header *FanWork::getHeader() const
{
    return header;
}

FanWork::Header::Header(const QString &ti, const QString &a, const QVector<QString> &ta):
    title(ti),
    author(a),
    publication_date(QDate::currentDate()),
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

const QDate &FanWork::Header::getPublicationDate() const
{
    return publication_date;
}

const QVector<QString> &FanWork::Header::getTags() const
{
    return tags;
}
