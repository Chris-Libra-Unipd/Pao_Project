#include "detailvisitor.h"
#include "moviedetail.h"
#include "songdetail.h"
#include "bookdetail.h"
#include "generalitemdetail.h"

void detailVisitor::visit(book* book){customWidget = new bookDetail(book);}

void detailVisitor::visit(movie* movie){customWidget = new movieDetail(movie);}

void detailVisitor::visit(song* song){customWidget = new songDetail(song);}

void detailVisitor::visit(generalItem* gItem){customWidget = new generalItemDetail(gItem);}

classDetail* detailVisitor::getWidget() const{return customWidget;}
