#ifndef FANWORK_H
#define FANWORK_H
#include<QString>
#include<QDate>
#include<QVector>
#include<memory>

class FanWork
{
public:
    class Header;
private:
    Header *header;
public:
    class Header
    {
    private:
        QString title, author, fandom;
        QDate publication_date;
        QVector<QString> tags;
    public:
        Header(const QString &ti, const QString &a, const QString &f, const QVector<QString> &ta);
        virtual ~Header();
        const QString &getTitle() const;
        const QString &getAuthor() const;
        const QString &getFandom() const;
        const QDate &getPublicationDate() const;
        const QVector<QString> &getTags() const;
    };

    FanWork(const Header &h);
    virtual ~FanWork();
    virtual FanWork *copy() const = 0;
    virtual const Header &getHeader() const;
};

#endif // FANWORK_H
