#ifndef DIGITAL_H
#define DIGITAL_H

#include "item.h"

class digital : virtual public item{
private:
    float size; //MB
    QString mediaPath;
public:
    digital(const float& siz, const QString& mdiaPath);
    digital() = default;

    float getSize() const;
    QString getMediaPath() const;

    void setSize(const float& siz);
    void setMediaPath(const QString& mdiaPath);

    void accept(jsonVisitor& jVisitor)const override;

    virtual bool isRelevant(const filter& filter) const override;
};

#endif // DIGITAL_H
