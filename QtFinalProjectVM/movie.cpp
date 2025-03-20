#include "movie.h"
#include <QJsonArray>
//movie class, as well as song, closes a diamond so it has to build the virtual base class "item"
movie::movie(const QDate& insDate,const QString& desc,const QString& imgPath,
      const QDate& pubDate, const QString& genre,const QString& title,
      const float& size, const QString& mdiaPath,
      const QVector<QString>& castv, const QString& direc, const QTime& durat) :
    item(insDate,desc,imgPath), media(pubDate,genre,title), digital(size, mdiaPath),
    cast(castv), director(direc), duration(durat){}

item* movie::clone() const{return new movie(*this);}

QVector<QString> movie::getCast() const{return cast;}

QString movie::getDirector() const{return director;}

QTime movie::getDuration() const{return duration;}

void movie::setCast(const QVector<QString>& castv){cast = castv;}

void movie::setDirector(const QString& direc){director  = direc;}

void movie::setDuration(const QTime& durat){duration = durat;}

void movie::accept(IVisitor& visitor){visitor.visit(this);}

void movie::accept(jsonVisitor& jVisitor)const{jVisitor.visit(*this);}

bool movie::isRelevant(const filter& filter) const{
    if(!media::isRelevant(filter))
        return 0;
    if(!digital::isRelevant(filter))
        return 0;

    //search a match in the cast vector
    if(filter.getActor() != nullptr){
        bool isPresent = 0;
        for(const QString& actor : cast){
            if(evaluateLCSS(actor, *(filter.getActor())) == 1)
                isPresent = 1;
        }
        if(!isPresent)
            return 0;
    }

    if(filter.getSizeMin() != nullptr && getSize() < *(filter.getSizeMin()))
        return 0;
    if(filter.getSizeMax() != nullptr && getSize() > *(filter.getSizeMax()))
        return 0;
    if(filter.getDurationMin() != nullptr && getDuration() < *(filter.getDurationMin()))
        return 0;
    if(filter.getDurationMax() != nullptr && getDuration() > *(filter.getDurationMax()))
        return 0;
    if(filter.getType() != nullptr && typeid(*filter.getType()) != typeid(*this))//dynamic type check
        return 0;
    if(filter.getArtist()!= nullptr || filter.getPagesMin() != nullptr || filter.getAuthor() != nullptr ||
        filter.getPagesMax() != nullptr)
        return 0;
    return 1;

}

float movie::howRelevant(const QString& keyword) const{
    //finds the maximum match score between the actors
    float actorScore = 0;
    for(const QString& actor : cast){
        float score = evaluateLCSS(actor,keyword);
        if(score > actorScore)
            actorScore = score;
    }
    float maxScore = 0;
    float temp;
    temp = item::howRelevant(keyword);
    if(temp > maxScore) maxScore = temp;
    temp = media::howRelevant(keyword);
    if(temp > maxScore) maxScore = temp;
    temp = mediumPriority * actorScore;
    if(temp > maxScore) maxScore = temp;
    temp = lowPriority * evaluateLCSS(director,keyword);
    if(temp > maxScore) maxScore = temp;
    return maxScore;
}



