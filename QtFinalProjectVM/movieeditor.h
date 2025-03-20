#ifndef MOVIEEDITOR_H
#define MOVIEEDITOR_H

#include "classeditor.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateTimeEdit>
#include <QFileDialog>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QListWidget>
#include "movie.h"

class movieEditor : public classEditor{
private:
    movie* moviePtr;

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
    QLabel* director;
    QLabel* actors;
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
    QLineEdit* directorInp;
    QListWidget* actorsList;
    QLineEdit* actorInp;
    QLineEdit* durInpH;
    QLineEdit* durInpM;
    QLineEdit* durInpS;
    QPushButton* findPath;
    QPushButton* findPathMedia;
    QPushButton* addActor;
    QPushButton* deleteActor;

    bool edit;
public:
    movieEditor(movie* moviePar, bool flag, QWidget* parent = nullptr);
    item* getItem() const override;

public slots:
    void updateFields();
    void updateImage();
    void addActorCommand();
    void deleteActorCommand();
    void updateMedia();

};

#endif // MOVIEEDITOR_H





