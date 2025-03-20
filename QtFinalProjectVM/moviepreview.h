#ifndef MOVIEPREVIEW_H
#define MOVIEPREVIEW_H

#include "classpreview.h"
#include "movie.h"

class moviePreview : public classPreview{
private:
    movie* moviePtr;

    QVBoxLayout* innerVLayout;
    QHBoxLayout* outerHLayout;
    QPushButton* type;
    QLabel* title;
    QLabel* genre;
    QLabel* director;
    QLabel* pubDate;
    QLabel* image;

public:
    moviePreview(movie* moviePar,QWidget* parent = nullptr);
};

#endif // MOVIEPREVIEW_H
