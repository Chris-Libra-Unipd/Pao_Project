#ifndef CLASSEDITOR_H
#define CLASSEDITOR_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateTimeEdit>
#include <QFileDialog>
#include <QPixmap>
#include <QListWidget>
#include <QMessageBox>
#include "item.h"


class classEditor : public QWidget{
    Q_OBJECT
protected:
    QLabel* header;
    QPushButton* confirm;
    QPushButton* cancel;
public:
    virtual ~classEditor() = 0;
    classEditor(QWidget* parent = nullptr);
    virtual item* getItem() const = 0;

signals:
    void accepted();
    void rejected();

};

#endif // CLASSEDITOR_H
