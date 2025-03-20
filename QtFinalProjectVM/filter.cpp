#include "filter.h"
#include "item.h"

filter::filter():
    insertionDateMin(nullptr), insertionDateMax(nullptr),
    publicationDateMin(nullptr), publicationDateMax(nullptr),
    durationMin(nullptr), durationMax(nullptr),
    genre(nullptr), actor(nullptr), author(nullptr), artist(nullptr),pagesMin(nullptr),
    pagesMax(nullptr),sizeMin(nullptr),sizeMax(nullptr), type(nullptr){}

const QDate* filter::getInsertionDateMin() const{return insertionDateMin;}
const QDate* filter::getInsertionDateMax() const{return insertionDateMax;}
const QDate* filter::getPublicationDateMin() const{return publicationDateMin;}
const QDate* filter::getPublicationDateMax() const{return publicationDateMax;}
const QTime* filter::getDurationMin() const{return durationMin;}
const QTime* filter::getDurationMax() const{return durationMax;}
const QString* filter::getGenre() const{return genre;}
const QString* filter::getActor() const{return actor;}
const QString* filter::getAuthor() const{return author;}
const QString* filter::getArtist() const{return artist;}
const unsigned int* filter::getPagesMin() const{return pagesMin;}
const unsigned int* filter::getPagesMax() const{return pagesMax;}
const float* filter::getSizeMin() const{return sizeMin;}
const float* filter::getSizeMax() const{return sizeMax;}
const item* filter::getType()const{return type;}

void filter::setInsertionDateMin(const QDate& iDateMin){
    if(insertionDateMin) *insertionDateMin = iDateMin;
    else insertionDateMin = new QDate(iDateMin);
}

void filter::setInsertionDateMax(const QDate& iDateMax){
    if(insertionDateMax) *insertionDateMax = iDateMax;
    else insertionDateMax = new QDate(iDateMax);
}

void filter::setPublicationDateMin(const QDate& pDateMin){
    if(publicationDateMin) *publicationDateMin = pDateMin;
    else publicationDateMin = new QDate(pDateMin);
}

void filter::setPublicationDateMax(const QDate& pDateMax){
    if(publicationDateMax) *publicationDateMax = pDateMax;
    else publicationDateMax = new QDate(pDateMax);
}

void filter::setDurationMin(const QTime& durMin){
    if(durationMin) *durationMin = durMin;
    else durationMin = new QTime(durMin);
}

void filter::setDurationMax(const QTime& durMax){
    if(durationMax) *durationMax = durMax;
    else durationMax = new QTime(durMax);
}

void filter::setGenre(const QString& genr){
    if(genre) *genre = genr;
    else genre = new QString(genr);
}

void filter::setActor(const QString& act){
    if(actor) *actor = act;
    else actor = new QString(act);
}

void filter::setAuthor(const QString& auth){
    if(author) *author = auth;
    else author = new QString(auth);
}

void filter::setArtist(const QString& art){
    if(artist) *artist = art;
    else artist = new QString(art);
}

void filter::setPagesMin(const unsigned int& pgMin){
    if(pagesMin) *pagesMin = pgMin;
    else pagesMin = new unsigned int(pgMin);
}

void filter::setPagesMax(const unsigned int& pgMax){
    if(pagesMax) *pagesMax = pgMax;
    else pagesMax = new unsigned int(pgMax);
}

void filter::setSizeMin(const float& szMin){
    if(sizeMin) *sizeMin = szMin;
    else sizeMin = new float(szMin);
}

void filter::setSizeMax(const float& szMax){
    if(sizeMax) *sizeMax = szMax;
    else sizeMax = new float(szMax);
}

void filter::setType(item* typ){
    if(type)
        delete type;
    type = typ;
}


filter::~filter(){
    //delete on nullptr pointers is safe
    delete insertionDateMin;
    delete insertionDateMax;
    delete publicationDateMin;
    delete publicationDateMax;
    delete durationMin;
    delete durationMax;
    delete genre;
    delete actor;
    delete author;
    delete artist;
    delete pagesMin;
    delete pagesMax;
    delete sizeMin;
    delete sizeMax;
    delete type;
}


