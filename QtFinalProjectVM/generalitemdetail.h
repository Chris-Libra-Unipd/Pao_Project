#ifndef GENERALITEMDETAIL_H
#define GENERALITEMDETAIL_H


#include "classdetail.h"
#include "generalitem.h"

class generalItemDetail : public classDetail{
private:
    generalItem* generalItemPtr;

    QVBoxLayout* topVLayout;
    QVBoxLayout* outerVLayout;
    QHBoxLayout* innerHLayout;

    QLabel* descr;
    QLabel* insDate;
    QLabel* name;
    QPushButton* type;
    QLabel* image;

public:
    generalItemDetail(generalItem* generalItemPar,QWidget* parent = nullptr);
};

#endif // GENERALITEMDETAIL_H
