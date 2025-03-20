#ifndef PREVIEWVISITOR_H
#define PREVIEWVISITOR_H

#include "IVisitor.h"
#include "classpreview.h"

class previewVisitor : public IVisitor{
private:
    classPreview* customWidget;
public:
    void visit(book* book)override;
    void visit(movie* movie)override;
    void visit(song* song)override;
    void visit(generalItem* gItem)override;
    classPreview* getWidget() const;
};


#endif // PREVIEWVISITOR_H
