#ifndef DETAILVISITOR_H
#define DETAILVISITOR_H

#include "IVisitor.h"
#include "classdetail.h"

class detailVisitor : public IVisitor{
private:
    classDetail* customWidget;
public:
    void visit(book* book)override;
    void visit(movie* movie)override;
    void visit(song* song)override;
    void visit(generalItem* gItem)override;
    classDetail* getWidget() const;
};

#endif // DETAILVISITOR_H
