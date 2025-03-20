#ifndef MEDIAPLAYERVISITOR_H
#define MEDIAPLAYERVISITOR_H

#include "IVisitor.h"
#include "classplayer.h"

class mediaPlayerVisitor : public IVisitor{
private:
    classPlayer* customWidget;
public:
    void visit(book* book)override;
    void visit(generalItem* gItem)override;
    void visit(movie* movie)override;
    void visit(song* song)override;
    classPlayer* getWidget() const;
};

#endif // MEDIAPLAYERVISITOR_H
