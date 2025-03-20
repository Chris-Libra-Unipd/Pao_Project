#ifndef SONG_H
#define SONG_H

#include "media.h"
#include "digital.h"

class song : public media, public digital{
private:
    QString artist;
    QTime duration;
public:

    song(const QDate& insDate,const QString& desc,const QString& imgPath,
         const QDate& pubDate, const QString& genre,const QString& title,
         const float& size, const QString& path,
         const QString& art, const QTime& durat);
    song() = default;

    QString getArtist() const;
    QTime getDuration() const;
    void setArtist(const QString& art);
    void setDuration(const QTime& durat);

    void accept(IVisitor& visitor) override;
    void accept(jsonVisitor& jVisitor)const override;

    bool isRelevant(const filter& filter) const override;
    float howRelevant(const QString& keyword) const override;

    item* clone() const override;


};

#endif // SONG_H
