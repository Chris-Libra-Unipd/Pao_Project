#include "addeditvisitor.h"
#include "bookeditor.h"
#include "movieeditor.h"
#include "songeditor.h"
#include "generalitemeditor.h"


addEditVisitor::addEditVisitor():customWidget(nullptr),edit(0){}

void addEditVisitor::setEditFlag(bool flag){edit = flag;}

classEditor* addEditVisitor::getWidget() const{return customWidget;}

void addEditVisitor::visit(book* book){customWidget = new bookEditor(book,edit);}

void addEditVisitor::visit(movie* movie){customWidget = new movieEditor(movie,edit);}

void addEditVisitor::visit(song* song){customWidget = new songEditor(song,edit);}

void addEditVisitor::visit(generalItem* gItem){customWidget = new generalItemEditor(gItem,edit);}
