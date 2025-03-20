#ifndef BOOKPREVIEW_H
#define BOOKPREVIEW_H

#include "classpreview.h"
#include "book.h"

class bookPreview : public classPreview{
private:
    book* bookPtr;

    QVBoxLayout* innerVLayout;
    QHBoxLayout* outerHLayout;

    QLabel* title;
    QLabel* genre;
    QLabel* author;
    QLabel* pubDate;
    QLabel* image;
    QPushButton* type;

public:
    bookPreview(book* bookPar,QWidget* parent = nullptr);
};
#endif // BOOKPREVIEW_H
