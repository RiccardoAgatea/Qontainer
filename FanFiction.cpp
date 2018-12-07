#include "FanFiction.h"

FanFiction::FanFiction(Header *h, const QVector<QString> &ch):
    FanWork(h),
    chapter_index(ch)
{

}

FanFiction::Bookmark::Bookmark(unsigned int num, const QString &com):
    chapter_number(num),
    comment(com)
{

}

FanFiction::Header::Header(const QString &ti, const QString &a, const QString &f,
                           const QVector<QString> &ta, unsigned int tot, unsigned int pub, unsigned int count,
                           const QString &lang):
    FanWork::Header(ti, a, f, ta),
    total_chapters(tot),
    published_chapters(pub),
    word_count(count),
    language(lang)
{

}
