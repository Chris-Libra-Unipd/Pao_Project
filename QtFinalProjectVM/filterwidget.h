#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "filter.h"
#include <QMessageBox>
#include <QTime>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QIcon>

class filterWidget : public QWidget{
    Q_OBJECT
private:
    //QPushButton* header;
    QPushButton* showHideButton;
    QLabel* insertionDate;
    QLabel* publicationDate;
    QLabel* duration;
    QLabel* genre;
    QLabel* actor;
    QLabel* author;
    QLabel* artist;
    QLabel* pages;
    QLabel* size;
    QLabel* type;

    QGridLayout* layout;
    QPushButton* confirm;
    QPushButton* resetButton;
    QPushButton* cancel;

    QLabel* min;
    QLabel* max;
    QLineEdit* insertionDateMinInp;
    QLineEdit* insertionDateMaxInp;
    QLineEdit* publicationDateMinInp;
    QLineEdit* publicationDateMaxInp;
    QLineEdit* durationMinHInp;
    QLineEdit* durationMinMInp;
    QLineEdit* durationMinSInp;
    QLineEdit* durationMaxHInp;
    QLineEdit* durationMaxMInp;
    QLineEdit* durationMaxSInp;
    QLineEdit* genreInp;
    QLineEdit* actorInp;
    QLineEdit* authorInp;
    QLineEdit* artistInp;
    QLineEdit* pagesMinInp;
    QLineEdit* pagesMaxInp;
    QLineEdit* sizeMinInp;
    QLineEdit* sizeMaxInp;
    QComboBox* typeInp;

    bool isHidden;
public:
    filterWidget(QWidget* parent = nullptr);

signals:
    void filterCreated(filter* filter);
    void appearenceChanged();

public slots:
    filter* buildFilter();
    void change();
    void reset();
};

#endif // FILTERWIDGET_H
