#include "item.h"

item::item(const QDate& insDate,const QString& desc, const QString& imgPath):
     insertionDate(insDate), description(desc), imagePath(imgPath){}

QDate item::getInsertionDate() const{return insertionDate;}

QString item::getDescription() const{return description;}

QString item::getImagePath() const{return imagePath;}

void item::setInsertionDate(const QDate& insDate){insertionDate = insDate;}

void item::setDescription(const QString& desc){description = desc;}

void item::setImagePath(const QString& imgPath){imagePath = imgPath;}

void item::accept(jsonVisitor& jVisitor)const{jVisitor.visit(*this);}

bool item::isRelevant(const filter& filter) const{
    if(filter.getInsertionDateMin() != nullptr && getInsertionDate() < *(filter.getInsertionDateMin()))
        return 0;
    if(filter.getInsertionDateMax() != nullptr && getInsertionDate() > *(filter.getInsertionDateMax()))
        return 0;
    return 1;
}

float item::howRelevant(const QString& keyword) const{
    float maxScore = 0;
    float temp;
    temp = lowPriority * evaluateLCSS(insertionDate.toString(Qt::ISODate), keyword);
    if(temp > maxScore) maxScore = temp;
    temp = lowPriority*evaluateLCSS(description, keyword);
    if(temp > maxScore) maxScore = temp;
    return maxScore;
}


