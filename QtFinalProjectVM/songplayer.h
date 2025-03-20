#ifndef SONGPLAYER_H
#define SONGPLAYER_H

#include "classplayer.h"
#include "song.h"

class songPlayer : public classPlayer{
private:
    const song* songPtr;
    QAudioOutput* auxOutput;
    QLabel* title;
    QLabel* artist;
    QLabel* pubDate;
    QLabel* img;
    QVBoxLayout* outerVLayout;
    QVBoxLayout* innerVLayout;
    QHBoxLayout* innerHLayout;
public:
    songPlayer(const song* songPar, QWidget* parent = nullptr);
};

#endif // SONGPLAYER_H
