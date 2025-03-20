#ifndef BOOKDETAIL_H
#define BOOKDETAIL_H

#include "classdetail.h"
#include "book.h"

class bookDetail : public classDetail{
private:
    book* bookPtr;

    QVBoxLayout* topVLayout;
    QVBoxLayout* outerVLayout;
    QHBoxLayout* innerHLayout;

    QLabel* descr;
    QLabel* insDate;
    QLabel* genre;
    QLabel* title;
    QLabel* pubDate;
    QLabel* author;
    QLabel* pages;
    QPushButton* type;
    QLabel* image;

public:
    bookDetail(book* bookPar,QWidget* parent = nullptr);
};

#endif // BOOKDETAIL_H
