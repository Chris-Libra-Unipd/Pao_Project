#ifndef MOVIEDETAIL_H
#define MOVIEDETAIL_H

#include "classdetail.h"
#include "movie.h"

class movieDetail : public classDetail{
private:
    movie* moviePtr;

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
    QLabel* director;
    QLabel* actors;
    QLabel* duration;

    QLabel* image;
    QPushButton* play;

public:
    movieDetail(movie* moviePar,QWidget* parent = nullptr);
};

#endif // MOVIEDETAIL_H
