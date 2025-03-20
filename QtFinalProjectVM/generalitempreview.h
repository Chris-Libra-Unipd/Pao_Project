#ifndef GENERALITEMPREVIEW_H
#define GENERALITEMPREVIEW_H

#include "classpreview.h"
#include "generalitem.h"

class generalItemPreview : public classPreview{
private:
    generalItem* generalItemPtr;

    QVBoxLayout* innerVLayout;
    QHBoxLayout* outerHLayout;
    QPushButton* type;
    QLabel* name;
    QLabel* image;

public:
    generalItemPreview(generalItem* generalItemPar,QWidget* parent = nullptr);
};

#endif // GENERALITEMPREVIEW_H
