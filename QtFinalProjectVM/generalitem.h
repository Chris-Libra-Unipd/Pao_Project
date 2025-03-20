#ifndef GENERALITEM_H
#define GENERALITEM_H

#include "item.h"

class generalItem : public item{
private:
    QString name;
public:
    generalItem(const QDate& insDate,const QString& desc,const QString& imgPath,
    const QString& nam);
    generalItem() = default;

    QString getName() const;
    void setName(const QString& nam);

    void accept(IVisitor& visitor) override;
    void accept(jsonVisitor& jVisitor)const override;

    float howRelevant(const QString& keyword) const override;
    bool isRelevant(const filter& filter)const override;

    item* clone() const override;

};

#endif // GENERALITEM_H
