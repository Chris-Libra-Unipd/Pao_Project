#ifndef MEDIA_H
#define MEDIA_H

#include "item.h"

class media : virtual public item{
private:
    QDate publicationDate;
    QString genre;
    QString title;
public:
    media(const QDate& pubDate, const QString& genr, const QString& titl);
    media() = default;

    QDate getPublicationDate() const;
    QString getGenre() const;
    QString getTitle() const;

    void setPublicationDate(const QDate& pubDate);
    void setGenre(const QString& genr);
    void setTitle(const QString& titl);

    void accept(jsonVisitor& jVisitor) const override;

    virtual bool isRelevant(const filter& filter) const override;
    virtual float howRelevant(const QString& keyword) const override;
};

#endif // MEDIA_H
