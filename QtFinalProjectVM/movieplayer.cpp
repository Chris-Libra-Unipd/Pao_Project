#include "movieplayer.h"

moviePlayer::moviePlayer(const movie* moviePar, QWidget* parent) : classPlayer(parent),
moviePtr(moviePar),
videoWidget(new QVideoWidget(this)),
auxOutput(new QAudioOutput(this)),
layout(new QVBoxLayout(this))
{
    //inherited fields
    timer = new QTimer(this);
    player = new QMediaPlayer(this);
    buttons = new playerButtonsWidget(player,timer,10,this);
    pBar = new QProgressBar(this);
    goBack = new QPushButton(QIcon(":/icons/back.png"),"",this);

    player->setSource(QUrl::fromLocalFile(moviePtr->getMediaPath()));
    player->setVideoOutput(videoWidget);
    player->setAudioOutput(auxOutput);
    player->setLoops(0);

    pBar->setTextVisible(0);
    timer->setInterval(250);

    layout->addWidget(goBack,0,Qt::AlignLeft);
    layout->addWidget(videoWidget,7);
    layout->addWidget(pBar);
    layout->addWidget(buttons);

    connect(timer, &QTimer::timeout, this, &moviePlayer::updatePBar);
    connect(player, &QMediaPlayer::positionChanged, this, [this]{updatePBar();});
    connect(goBack, &QPushButton::clicked, this, &moviePlayer::goBackClicked);
}
