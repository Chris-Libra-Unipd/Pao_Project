#include "generalitem.h"

generalItem::generalItem(const QDate& insDate,const QString& desc,const QString& imgPath,
            const QString& nam):
    item(insDate,desc,imgPath), name(nam){}

item* generalItem::clone() const{return new generalItem(*this);}

QString generalItem::getName() const{return name;}

void generalItem::setName(const QString& nam){name = nam;}

void generalItem::accept(IVisitor& visitor){visitor.visit(this);}

void generalItem::accept(jsonVisitor& jVisitor) const{jVisitor.visit(*this);}

float generalItem::howRelevant(const QString& keyword) const{
    float maxScore = 0;
    float temp;
    temp = item::howRelevant(keyword);
    if(temp > maxScore) maxScore = temp;
    temp = highPriority * evaluateLCSS(name,keyword);
    if(temp > maxScore) maxScore = temp;
    return maxScore;
}

bool generalItem::isRelevant(const filter& filter)const{
    if(!item::isRelevant(filter))
        return 0;
    if(filter.getType() != nullptr && typeid(*filter.getType()) != typeid(*this))//dynamic type check
        return 0;
    if(filter.getActor() != nullptr || filter.getArtist()!= nullptr || filter.getDurationMax() != nullptr ||
        filter.getDurationMax() != nullptr || filter.getSizeMax() != nullptr || filter.getSizeMax() != nullptr ||
        filter.getAuthor() != nullptr || filter.getGenre() != nullptr || filter.getPagesMin() != nullptr ||
        filter.getPagesMax() != nullptr || filter.getPublicationDateMin() != nullptr || filter.getPublicationDateMax() != nullptr)
        return 0;
    return 1;
}

