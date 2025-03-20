#ifndef JSONVISITOR_H
#define JSONVISITOR_H

#include <QJsonObject>

class item;
class media;
class digital;
class book;
class movie;
class song;
class generalItem;
class collection;

class jsonVisitor{
private:
    QJsonObject jObj;
public:
    QJsonObject getObject();
    virtual void visit(const item& item);
    virtual void visit(const media& media);
    virtual void visit(const digital& digital);
    virtual void visit(const book& book);
    virtual void visit(const movie& movie);
    virtual void visit(const song& song);
    virtual void visit(const generalItem& gItem);
    virtual void visit(const collection& coll);
};

#endif // JSONVISITOR_H
