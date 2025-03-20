#include "classplayer.h"

classPlayer::~classPlayer() = default;
classPlayer::classPlayer(QWidget* parent) : QWidget(parent){}

void classPlayer::play(){buttons->play();}

void classPlayer::pause(){buttons->pause();}

void classPlayer::updatePBar(){
    pBar->setValue((float(player->position())/float(player->duration()))*100);
}
