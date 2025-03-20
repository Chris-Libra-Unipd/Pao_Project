#ifndef MOVIE_H
#define MOVIE_H

#include <QVector>
#include "media.h"
#include "digital.h"

class movie :public media, public digital{
private:
    QVector<QString> cast;
    QString director;
    QTime duration;

public:
    movie(const QDate& insDate,const QString& desc,const QString& imgPath,
          const QDate& pubDate, const QString& genre,const QString& title,
          const float& size, const QString& mdiaPath,
          const QVector<QString>& castv, const QString& direc, const QTime& durat);
    movie() = default;

    QVector<QString> getCast() const;
    QString getDirector() const;
    QTime getDuration() const;
    void setCast(const QVector<QString>& castv);
    void setDirector(const QString& direc);
    void setDuration(const QTime& durat);

    bool isRelevant(const filter& filter) const override;
    float howRelevant(const QString& keyword) const override;

    void accept(IVisitor& visitor) override;
    void accept(jsonVisitor& jVisitor) const override;

    item* clone() const override;

};

#endif // MOVIE_H
