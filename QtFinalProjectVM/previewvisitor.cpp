#include "previewvisitor.h"
#include "moviepreview.h"
#include "songpreview.h"
#include "bookpreview.h"
#include "generalitempreview.h"

void previewVisitor::visit(book* book){customWidget = new bookPreview(book);}

void previewVisitor::visit(movie* movie){customWidget = new moviePreview(movie);}

void previewVisitor::visit(song* song){customWidget = new songPreview(song);}

void previewVisitor::visit(generalItem* gItem){customWidget = new generalItemPreview(gItem);}

classPreview* previewVisitor::getWidget() const{return customWidget;}
