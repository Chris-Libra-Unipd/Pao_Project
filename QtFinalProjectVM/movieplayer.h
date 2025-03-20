#ifndef MOVIEPLAYER_H
#define MOVIEPLAYER_H

#include "classplayer.h"
#include "movie.h"

class moviePlayer : public classPlayer{
private:
    const movie* moviePtr;
    QVideoWidget* videoWidget;
    QAudioOutput* auxOutput;
    QVBoxLayout* layout;

public:
    moviePlayer(const movie* moviePar, QWidget* parent = nullptr);
};

#endif // MOVIEPLAYER_H
