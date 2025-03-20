#include "generalitempreview.h"

generalItemPreview::generalItemPreview(generalItem* generalItemPar,QWidget* parent): classPreview(parent),
    generalItemPtr(generalItemPar),
    innerVLayout(new QVBoxLayout()),
    outerHLayout(new QHBoxLayout(this)),
    type(new QPushButton(QIcon(":/icons/box.png"),"",this)),
    name(new QLabel(this)),
    image(new QLabel(this))
{
    //body
    image->setPixmap(QPixmap(generalItemPtr->getImagePath()).scaled(this->width()*0.2,this->width()*0.2,Qt::KeepAspectRatio));
    name->setText("Name: "+generalItemPtr->getName());

    remove = new QPushButton(QIcon(":/icons/delete.png"),"",this);
    details = new QPushButton(QIcon(":/icons/info.png"),"",this);

    innerVLayout->addWidget(name);
    innerVLayout->addWidget(type,0,Qt::AlignLeft);
    innerVLayout->addStretch();

    outerHLayout->addWidget(image);
    outerHLayout->addLayout(innerVLayout);
    outerHLayout->addStretch();
    outerHLayout->addWidget(details,0,Qt::AlignBottom);
    outerHLayout->addWidget(remove,0,Qt::AlignBottom);

    setMinimumHeight(sizeHint().height());
    setMaximumHeight(sizeHint().height());

    connect(remove,&QPushButton::clicked,this,[this]{emit sendRemoveRequest(generalItemPtr);});
    connect(details,&QPushButton::clicked,this,[this]{emit sendDetailsRequest(generalItemPtr);});
}
