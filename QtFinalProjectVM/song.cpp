#include "song.h"

song::song(const QDate& insDate,const QString& desc,const QString& imgPath,
     const QDate& pubDate, const QString& genre,const QString& title,
     const float& size, const QString& path,
     const QString& art, const QTime& durat) :
    item(insDate,desc,imgPath),media(pubDate,genre,title),digital(size,path),artist(art),duration(durat){}

item* song::clone() const{return new song(*this);}

QString song::getArtist() const{return artist;}

QTime song::getDuration() const{return duration;}

void song::setArtist(const QString& art){artist = art;}

void song::setDuration(const QTime& durat){duration = durat;}

void song::accept(IVisitor& visitor){visitor.visit(this);}

void song::accept(jsonVisitor& jVisitor)const{jVisitor.visit(*this);}

bool song::isRelevant(const filter& filter) const{
    if(!media::isRelevant(filter))
        return 0;
    if(!digital::isRelevant(filter))
        return 0;
    if(filter.getArtist() != nullptr && evaluateLCSS(getArtist(), *(filter.getArtist())) < 1)
        return 0;
    if(filter.getDurationMin() != nullptr && getDuration() < *(filter.getDurationMin()))
        return 0;
    if(filter.getDurationMax() != nullptr && getDuration() > *(filter.getDurationMax()))
        return 0;
    if(filter.getSizeMin() != nullptr && getSize() < *(filter.getSizeMin()))
        return 0;
    if(filter.getSizeMax() != nullptr && getSize() > *(filter.getSizeMax()))
        return 0;
    if(filter.getType() != nullptr && typeid(*filter.getType()) != typeid(*this))//dynamic type check
        return 0;
    if(filter.getActor() != nullptr || filter.getAuthor() != nullptr || filter.getPagesMin() != nullptr ||
        filter.getPagesMax() != nullptr)
        return 0;
    return 1;
}

float song::howRelevant(const QString& keyword) const{
    float maxScore = 0;
    float temp;
    temp = item::howRelevant(keyword);
    if(temp > maxScore) maxScore = temp;
    temp = media::howRelevant(keyword);
    if(temp > maxScore) maxScore = temp;
    temp = mediumPriority * evaluateLCSS(artist,keyword);
    if(temp > maxScore) maxScore = temp;
    return maxScore;
}


