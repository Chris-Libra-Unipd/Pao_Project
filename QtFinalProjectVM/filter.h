#ifndef FILTER_H
#define FILTER_H
#include <QString>
#include <QDate>


class item;

class filter{
private:
    QDate* insertionDateMin;
    QDate* insertionDateMax;
    QDate* publicationDateMin;
    QDate* publicationDateMax;
    QTime* durationMin;
    QTime* durationMax;
    QString* genre;
    QString* actor;
    QString* author;
    QString* artist;
    unsigned int* pagesMin;
    unsigned int* pagesMax;
    float* sizeMin;
    float* sizeMax;
    item* type;
public:

    //every field is set to nullptr
    filter();
    ~filter();

    const QDate* getInsertionDateMin() const;
    const QDate* getInsertionDateMax() const;
    const QDate* getPublicationDateMin() const;
    const QDate* getPublicationDateMax() const;
    const QTime* getDurationMin() const;
    const QTime* getDurationMax() const;
    const QString* getGenre() const;
    const QString* getActor() const;
    const QString* getAuthor() const;
    const QString* getArtist() const;
    const unsigned int* getPagesMin() const;
    const unsigned int* getPagesMax() const;
    const float* getSizeMin() const;
    const float* getSizeMax() const;
    const item* getType()const;

    void setInsertionDateMin(const QDate& iDateMin);
    void setInsertionDateMax(const QDate& iDateMax);
    void setPublicationDateMin(const QDate& pDateMin);
    void setPublicationDateMax(const QDate& pDateMax);
    void setDurationMin(const QTime& durMin);
    void setDurationMax(const QTime& durMax);
    void setGenre(const QString& genr);
    void setActor(const QString& act);
    void setAuthor(const QString& aut);
    void setArtist(const QString& art);
    void setPagesMin(const unsigned int& pgMin);
    void setPagesMax(const unsigned int& pgMax);
    void setSizeMin(const float& szMin);
    void setSizeMax(const float& szMax);
    void setType(item* typ);

};

#endif // FILTER_H
