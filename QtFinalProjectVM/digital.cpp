#include "digital.h"

//doesn't need to build subobject of type "item" because digital is an abstract pure class,
//when this constructor is called by a concrete item (i.e. song) the subobject of type "item" has already been constructed
digital::digital(const float& siz, const QString& mdiaPath) : size(siz), mediaPath(mdiaPath){}

float digital::getSize() const{return size;}

QString digital::getMediaPath() const{return mediaPath;}

void digital::setSize(const float& siz){size = siz;}

void digital::setMediaPath(const QString& mdiaPath){mediaPath = mdiaPath;}

void digital::accept(jsonVisitor& jVisitor)const{jVisitor.visit(*this);}

//if the subobject "item"  is relevant and all the data fields respect the filter's requirements then the object is relevant
bool digital::isRelevant(const filter& filter) const{
    if(!item::isRelevant(filter))
        return 0;
    if(filter.getSizeMin() != nullptr && getSize() < *(filter.getSizeMin()))
        return 0;
    if(filter.getSizeMax() != nullptr && getSize() > *(filter.getSizeMax()))
        return 0;
    return 1;
}

