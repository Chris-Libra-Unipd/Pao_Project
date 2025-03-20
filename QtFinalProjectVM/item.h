#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QDate>
#include <QJsonObject>
#include "filter.h"
#include "IVisitor.h"
#include "jsonVisitor.h"
#include "utilityfunctions.h"
#include <typeinfo>

class item{
private:
    QDate insertionDate;
    QString description;
    QString imagePath;
protected:
    //constant static values needed for the pertinence evaluation of the concrete classes (so protected) during a research
    static constexpr float lowPriority = 1.2;
    static constexpr float mediumPriority = 1.5;
    static constexpr float highPriority = 2;
public:
    virtual ~item() = default;
    item(const QDate& insDate,const QString& desc, const QString& imgPath);
    item() = default;

    QDate getInsertionDate() const;
    QString getDescription() const;
    QString getImagePath() const;

    void setInsertionDate(const QDate& insDate);
    void setDescription(const QString& desc);
    void setImagePath(const QString& imgPath);

    virtual bool isRelevant(const filter& filter) const;        //filter relevance evalutation
    virtual float howRelevant(const QString& keyword) const;    //research relevance evaluation

    virtual void accept(IVisitor& visitor) = 0;                 //GUI widget creation
    virtual void accept(jsonVisitor& jVisitor) const;           //data persistance

    virtual item* clone() const = 0;

};

#endif // ITEM_H
