#ifndef ADDEDITVISITOR_H
#define ADDEDITVISITOR_H

#include "IVisitor.h"
#include "classeditor.h"

class addEditVisitor : public IVisitor{
private:
    classEditor* customWidget;
    bool edit;
public:
    addEditVisitor();
    void setEditFlag(bool flag);
    void visit(book* book)override;
    void visit(movie* movie)override;
    void visit(song* song)override;
    void visit(generalItem* gItem)override;
    classEditor* getWidget() const;
};

#endif // ADDEDITVISITOR_H
