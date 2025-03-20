#ifndef BOOK_H
#define BOOK_H

#include "media.h"

class book : public media{
private:
    QString author;
    unsigned int pages;
public:
    book(const QDate& insDate,const QString& desc, const QString& imgPath,
        const QDate& pubDate, const QString& genre,const QString& title,
        const QString& auth, const unsigned int& pg);
    book() = default;

    QString getAuthor() const;
    unsigned int getPages() const;

    void setAuthor(const QString& auth);
    void setPages(const unsigned int& pg);

    bool isRelevant(const filter& filter) const override;
    float howRelevant(const QString& keyword) const override;

    void accept(IVisitor& visitor) override;
    void accept(jsonVisitor& jVisitor)const override;

    item* clone() const override;

};

#endif // BOOK_H
