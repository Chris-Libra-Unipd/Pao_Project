#include "book.h"

book::book(const QDate& insDate,const QString& desc, const QString& imgPath,
     const QDate& pubDate, const QString& genre,const QString& title,
     const QString& auth, const unsigned int& pg) :
     item(insDate,desc,imgPath), media(pubDate,genre,title), author(auth), pages(pg){}

QString book::getAuthor() const{return author;}

item* book::clone() const{return new book(*this);}

unsigned int book::getPages() const{return pages;}

void book::setAuthor(const QString& auth){author = auth;}

void book::setPages(const unsigned int& pg){pages = pg;}

void book::accept(IVisitor& visitor){visitor.visit(this);}

void book::accept(jsonVisitor& jVisitor)const{jVisitor.visit(*this);}

bool book::isRelevant(const filter& filter) const{
    //if a field in the filter is != nullptr it's active so its relevance is checked
    if(!media::isRelevant(filter))
        return 0;
    if(filter.getAuthor() != nullptr &&  evaluateLCSS(getAuthor(),*(filter.getAuthor())) < 1)
        return 0;
    if(filter.getPagesMin() != nullptr && getPages() < *(filter.getPagesMin()))
        return 0;
    if(filter.getPagesMax() != nullptr && getPages() > *(filter.getPagesMax()))
        return 0;
    if(filter.getType() != nullptr && typeid(*filter.getType()) != typeid(*this))//dynamic type field check
        return 0;
    //if the filter has fields related to other concrete types then make the object not relevant
    if(filter.getActor() != nullptr || filter.getArtist()!= nullptr || filter.getDurationMax() != nullptr
        || filter.getDurationMax() != nullptr || filter.getSizeMax() != nullptr || filter.getSizeMax() != nullptr)
        return 0;
    return 1;
}

float book::howRelevant(const QString& keyword) const{
    //the score of an object is the maximum of the scores of each data field
    //each data field has a different weight related to its importance to the search
    //there are 3 levels of importance: low, medium, high.
    float maxScore = 0;
    float temp;
    temp = item::howRelevant(keyword);
    if(temp > maxScore) maxScore = temp;
    temp = media::howRelevant(keyword);
    if(temp > maxScore) maxScore = temp;
    temp = mediumPriority * evaluateLCSS(author,keyword);
    if(temp > maxScore) maxScore = temp;
    return maxScore;
}


