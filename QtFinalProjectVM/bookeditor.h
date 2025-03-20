#ifndef BOOKEDIT_H
#define BOOKEDIT_H

#include "classeditor.h"
#include "book.h"


class bookEditor : public classEditor{
private:
    book* bookPtr;

    QGridLayout* Glayout;
    QVBoxLayout* layout;

    QLabel* descr;
    QLabel* pubDate;
    QLabel* genre;
    QLabel* title;
    QLabel* author;
    QLabel* pages;
    QLabel* insDate;
    QLabel* imgPath;
    QLabel* image;

    QTextEdit* descrInp;
    QDateTimeEdit* pubDateInp;
    QDateTimeEdit* insDateInp;
    QLineEdit* genreInp;
    QLineEdit* titleInp;
    QLineEdit* authorInp;
    QLineEdit* pagesInp;
    QLineEdit* imgPathInp;
    QPushButton* findPath;

    bool edit;
public:
    bookEditor(book* bookPar, bool flag, QWidget* parent = nullptr);
    item* getItem() const override;

public slots:
    void updateFields();
    void updateImage();
};

#endif // BOOKEDIT_H
