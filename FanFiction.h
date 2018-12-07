#ifndef FANFICTION_H
#define FANFICTION_H
#include"FanWork.h"

class FanFiction : public FanWork
{
private:
    QVector<QString> chapter_index;
public:
    class Bookmark
    {
    private:
        unsigned int chapter_number;
        QString comment;
    public:
        Bookmark(unsigned int num = 0, const QString &com = "");
    };

    class Header: public FanWork::Header
    {
    private:
        unsigned int total_chapters, published_chapters;
        unsigned int word_count;
        QString language;

    public:
        Header(const QString &ti, const QString &a, const QString &f, const QVector<QString> &ta,
               unsigned int tot, unsigned int pub, unsigned int count, const QString &lang);
    };

    FanFiction(Header *h, const QVector<QString> &ch);
};

#endif // FANFICTION_H
