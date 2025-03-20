#ifndef SONGDETAIL_H
#define SONGDETAIL_H


#include "classdetail.h"
#include "song.h"

class songDetail : public classDetail{
private:
    song* songPtr;

    QVBoxLayout* topVLayout;
    QVBoxLayout* outerVLayout;
    QHBoxLayout* innerHLayout;
    QPushButton* type;
    QLabel* descr;
    QLabel* insDate;
    QLabel* genre;
    QLabel* title;
    QLabel* pubDate;
    QLabel* size;
    QLabel* artist;
    QLabel* duration;

    QLabel* image;
    QPushButton* play;

public:
    songDetail(song* songPar,QWidget* parent = nullptr);
};
#endif // SONGDETAIL_H
