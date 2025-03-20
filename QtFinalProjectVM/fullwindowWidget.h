#ifndef FULLWINDOWWIDGET_H
#define FULLWINDOWWIDGET_H

#include <QMainWindow>
#include "toolbarWidget.h"
#include "bodyWidget.h"
#include <QVBoxLayout>
#include "collection.h"
#include <QDialog>
#include <QCloseEvent>
#include <QFile>

class fullWindow : public QMainWindow{
    Q_OBJECT
private:
    bool changesFlag;
    collection* itemsColl;
    QWidget* container;
    QVBoxLayout* layout;
    body* bodyW;
    toolBar* toolB;
public:
    fullWindow(QWidget* parent = nullptr);
    void closeEvent(QCloseEvent* event) override;

};

#endif // FULLWINDOWWIDGET_H
