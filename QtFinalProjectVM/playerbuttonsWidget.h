#ifndef PLAYERBUTTONSWIDGET_H
#define PLAYERBUTTONSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMediaPlayer>
#include <QIcon>
#include <QTimer>

class playerButtonsWidget : public  QWidget{
    Q_OBJECT
private:
    bool isPaused;
    unsigned int stepSec;
    QIcon* stopIcon;
    QIcon* playIcon;
    QIcon* pauseIcon;
    QPushButton* forward;
    QPushButton* backward;
    QPushButton* play_pause;
    QPushButton* stop;
    QHBoxLayout* layout;
    QMediaPlayer* playerPtr;
    QTimer* timerPtr;

public:
    playerButtonsWidget(QMediaPlayer* player,QTimer* timer,const unsigned int& step = 5,QWidget* parent = nullptr);

public slots:
    void updatePP();
    void play();
    void pause();
};

#endif // PLAYERBUTTONSWIDGET_H
