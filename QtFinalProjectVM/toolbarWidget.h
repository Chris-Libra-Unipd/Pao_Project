#ifndef TOOLBARWIDGET_H
#define TOOLBARWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QIcon>
#include <QHBoxLayout>
#include "collection.h"
#include <QDialog>
#include <QLabel>
#include <QShortcut>
#include <QPainter>
#include <QStyleOption>
#include <QPaintEvent>

class toolBar : public  QWidget{
    Q_OBJECT
private:
    collection* ICollection;
    QPushButton* saveAs;
    QPushButton* newCollection;
    QPushButton* open;
    QHBoxLayout* layout;

    QShortcut* newCollShortcut;
    QShortcut* saveCollShortcut;
    QShortcut* openCollShortcut;

public:
    toolBar(collection* coll, QWidget* parent = nullptr);
    void paintEvent(QPaintEvent * event) override;

public slots:
    void saveDialog(collection* coll);
    void saveColl();
    void openColl();
    void createColl();

signals:
    void collectionChanged();
    void collectionSaved();

};

#endif // TOOLBARWIDGET_H
