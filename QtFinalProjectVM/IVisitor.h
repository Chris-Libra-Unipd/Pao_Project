#ifndef IVISITOR_H
#define IVISITOR_H

#include <QWidget>

class book;
class movie;
class song;
class generalItem;

class IVisitor{
public:
    virtual ~IVisitor() = default;
    virtual void visit(book* book) = 0;
    virtual void visit(movie* movie) = 0;
    virtual void visit(song* song) = 0;
    virtual void visit(generalItem* gItem) = 0;
};

#endif // IVISITOR_H
