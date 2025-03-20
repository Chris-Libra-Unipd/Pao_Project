#include "songplayer.h"

songPlayer::songPlayer(const song* songPar, QWidget* parent) :  classPlayer(parent),
songPtr(songPar),
auxOutput(new QAudioOutput(this)),
title(new QLabel("Title: "+ songPtr->getTitle(),this)),
artist(new QLabel("Artist: "+ songPtr->getArtist(),this)),
pubDate(new QLabel("Publication date: "+ songPtr->getPublicationDate().toString(Qt::ISODate),this)),
img(new QLabel(this)),
outerVLayout(new QVBoxLayout(this)),
innerVLayout(new QVBoxLayout()),
innerHLayout(new QHBoxLayout())
{
    //inherited fields
    timer = new QTimer(this);
    player = new QMediaPlayer(this);
    buttons = new playerButtonsWidget(player,timer,5,this);
    pBar = new QProgressBar(this);
    goBack = new QPushButton(QIcon(":/icons/back.png"),"",this);

    player->setAudioOutput(auxOutput);
    player->setSource(QUrl::fromLocalFile(songPtr->getMediaPath()));
    player->setLoops(0);

    img->setPixmap(QPixmap(songPtr->getImagePath()).scaled(this->width()*0.5,this->width()*0.5,Qt::KeepAspectRatio));

    pBar->setTextVisible(0);
    timer->setInterval(250);

    innerHLayout->addWidget(goBack,0,Qt::AlignTop);
    innerHLayout->addWidget(img,0,Qt::AlignTop);

    innerVLayout->addWidget(title);
    innerVLayout->addWidget(artist);
    innerVLayout->addWidget(pubDate);
    innerVLayout->addStretch();
    innerVLayout->addWidget(buttons);

    innerHLayout->addLayout(innerVLayout);
    innerHLayout->addStretch();

    outerVLayout->addLayout(innerHLayout);
    outerVLayout->addWidget(pBar);
    outerVLayout->addStretch();

    QObject::connect(timer, &QTimer::timeout, this, &songPlayer::updatePBar);
    connect(player, &QMediaPlayer::positionChanged, this, [this]{updatePBar();});
    connect(goBack, &QPushButton::clicked, this, &songPlayer::goBackClicked);

}
