#include "mediaplayervisitor.h"
#include "songplayer.h"
#include "movieplayer.h"

classPlayer* mediaPlayerVisitor::getWidget() const{return customWidget;}

void mediaPlayerVisitor::visit(book* book){
    qWarning("cannot play a non digital item\n");
    customWidget = nullptr;
}
void mediaPlayerVisitor::visit(generalItem* gItem){
    qWarning("cannot play a non digital item\n");
    customWidget = nullptr;
}

void mediaPlayerVisitor::visit(movie* movie){customWidget = new moviePlayer(movie);}

void mediaPlayerVisitor::visit(song* song){customWidget = new songPlayer(song);}

