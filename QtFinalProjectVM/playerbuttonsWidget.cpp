#include "playerbuttonsWidget.h"

playerButtonsWidget::playerButtonsWidget(QMediaPlayer* player,QTimer* timer ,const unsigned int& step,QWidget* parent):QWidget(parent),
    isPaused(1),
    stepSec(step),
    stopIcon(new QIcon(":/icons/stop.png")),
    playIcon(new QIcon(":/icons/play.png")),
    pauseIcon(new QIcon(":/icons/pause.png")),
    forward(new QPushButton("+ "+QString::number(stepSec)+" sec",this)),
    backward(new QPushButton("- "+QString::number(stepSec)+" sec",this)),
    play_pause(new QPushButton(*playIcon,"",this)),
    stop(new QPushButton(*stopIcon,"",this)),
    layout(new QHBoxLayout(this)),
    playerPtr(player),
    timerPtr(timer)
{

    layout->addWidget(backward);
    layout->addWidget(play_pause);
    layout->addWidget(stop);
    layout->addWidget(forward);

    connect(play_pause, &QPushButton::clicked, this, &playerButtonsWidget::updatePP);
    connect(stop, &QPushButton::clicked, playerPtr, [this, player]{player->stop(); pause();});
    connect(forward, &QPushButton::clicked, playerPtr, [this]{
        playerPtr->setPosition(playerPtr->position()+1000*stepSec);
    });
    connect(backward, &QPushButton::clicked, playerPtr, [this]{
        playerPtr->setPosition(playerPtr->position()-1000*stepSec);
    });

}

void playerButtonsWidget::play(){
    isPaused = 0;
    play_pause->setIcon(*pauseIcon);
    playerPtr->play();
    timerPtr->start();
}

void playerButtonsWidget::pause(){
    isPaused = 1;
    play_pause->setIcon(*playIcon);
    playerPtr->pause();
    timerPtr->stop();
}

void playerButtonsWidget::updatePP(){
    if(isPaused == 1)
        play();
    else
        pause();
}
