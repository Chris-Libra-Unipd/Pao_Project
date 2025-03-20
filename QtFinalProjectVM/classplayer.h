#ifndef CLASSPLAYER_H
#define CLASSPLAYER_H

#include "playerbuttonsWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>
#include "QProgressBar"
#include "QTimer"
#include "QPixmap"
#include "QLabel"
#include <QIcon>

class classPlayer : public QWidget{
    Q_OBJECT
protected:
    QMediaPlayer* player;
    playerButtonsWidget* buttons;
    QProgressBar* pBar;
    QTimer* timer;
    QPushButton* goBack;
public:
    virtual ~classPlayer() = 0;
    classPlayer(QWidget* parent = nullptr);

public slots:
    void play();
    void pause();
    void updatePBar();

signals:
    void goBackClicked();
};

#endif // CLASSPLAYER_H
