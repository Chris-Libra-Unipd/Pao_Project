#ifndef GENERALITEMEDITOR_H
#define GENERALITEMEDITOR_H

#include "classeditor.h"
#include "generalitem.h"

class generalItemEditor : public classEditor{
private:
    generalItem* generalItemPtr;

    QGridLayout* Glayout;
    QVBoxLayout* layout;

    QLabel* descr;
    QLabel* insDate;
    QLabel* imgPath;
    QLabel* name;

    QLabel* image;

    QTextEdit* descrInp;
    QDateTimeEdit* insDateInp;
    QLineEdit* imgPathInp;
    QLineEdit* nameInp;
    QPushButton* findPath;
    bool edit;

public:
    generalItemEditor(generalItem* generalItemPar, bool flag, QWidget* parent = nullptr);
    item* getItem() const override;

public slots:
    void updateFields();
    void updateImage();
};

#endif // GENERALITEMEDITOR_H
