#ifndef SONGEDITOR_H
#define SONGEDITOR_H

#include "classeditor.h"
#include "song.h"

class songEditor : public classEditor{
private:
    song* songPtr;

    QGridLayout* Glayout;
    QVBoxLayout* layout;

    QLabel* descr;
    QLabel* insDate;
    QLabel* imgPath;
    QLabel* genre;
    QLabel* title;
    QLabel* pubDate;
    QLabel* mediaPath;
    QLabel* size;
    QLabel* artist;
    QLabel* duration;

    QLabel* image;

    QTextEdit* descrInp;
    QDateTimeEdit* insDateInp;
    QLineEdit* imgPathInp;
    QLineEdit* genreInp;
    QLineEdit* titleInp;
    QDateTimeEdit* pubDateInp;
    QLineEdit* mediaPathInp;
    QLineEdit* sizeInp;
    QLineEdit* artistInp;
    QLineEdit* durInpH;
    QLineEdit* durInpM;
    QLineEdit* durInpS;
    QPushButton* findPath;
    QPushButton* findPathMedia;
    bool edit;

public:
    songEditor(song* songPar, bool flag, QWidget* parent = nullptr);
    item* getItem() const override;
public slots:
    void updateFields();
    void updateImage();
    void updateMedia();
};

#endif // SONGEDITOR_H
