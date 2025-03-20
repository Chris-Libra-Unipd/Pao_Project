#include "media.h"

media::media(const QDate& pubDate, const QString& genr, const QString& titl):
    publicationDate(pubDate), genre(genr), title(titl){}

QDate media::getPublicationDate() const{return publicationDate;}

QString media::getGenre() const{return genre;}

QString media::getTitle() const{return title;}

void media::setPublicationDate(const QDate& pubDate){publicationDate = pubDate;}

void media::setGenre(const QString& genr){genre = genr;}

void media::setTitle(const QString& titl){title = titl;}

void media::accept(jsonVisitor& jVisitor) const{jVisitor.visit(*this);}

bool media::isRelevant(const filter& filter) const{
    if(!item::isRelevant(filter))
        return 0;
    if(filter.getPublicationDateMin() != nullptr && getPublicationDate() < *(filter.getPublicationDateMin()))
        return 0;
    if(filter.getPublicationDateMax() != nullptr && getPublicationDate() > *(filter.getPublicationDateMax()))
        return 0;
    //check with evaluateLCSS looks for a case insensitive match, a full match returns 1, otherwise < 1
    if(filter.getGenre() != nullptr && evaluateLCSS(getGenre(),*(filter.getGenre())) < 1)
        return 0;
    return 1;
}

float media::howRelevant(const QString& keyword) const{
    float maxScore = 0;
    float temp;
    temp = mediumPriority*evaluateLCSS(publicationDate.toString(Qt::ISODate),keyword);
    if(temp>maxScore)maxScore = temp;
    temp = highPriority*evaluateLCSS(genre,keyword);
    if(temp>maxScore)maxScore = temp;
    temp = highPriority*evaluateLCSS(title,keyword);
    if(temp>maxScore)maxScore = temp;
    return maxScore;
}

