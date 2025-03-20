#ifndef SONGPREVIEW_H
#define SONGPREVIEW_H

#include "classpreview.h"
#include "song.h"

class songPreview : public classPreview{
private:
    song* songPtr;

    QVBoxLayout* innerVLayout;
    QHBoxLayout* outerHLayout;
    QPushButton* type;
    QLabel* title;
    QLabel* genre;
    QLabel* artist;
    QLabel* pubDate;
    QLabel* image;

public:
    songPreview(song* songPar,QWidget* parent = nullptr);
};

#endif // SONGPREVIEW_H
