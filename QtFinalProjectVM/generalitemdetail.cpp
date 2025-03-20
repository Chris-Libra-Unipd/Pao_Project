#include "generalitemdetail.h"

generalItemDetail::generalItemDetail(generalItem* generalItemPar,QWidget* parent): classDetail(parent),
    generalItemPtr(generalItemPar),
    topVLayout(new QVBoxLayout()),
    outerVLayout(new QVBoxLayout(this)),
    innerHLayout(new QHBoxLayout()),
    descr(new QLabel(this)),
    insDate(new QLabel(this)),
    name(new QLabel(this)),
    type(new QPushButton(QIcon(":/icons/box.png"),"",this)),
    image(new QLabel(this))
{
    //body
    image->setPixmap(QPixmap(generalItemPtr->getImagePath()).scaled(this->width()*0.5,this->width()*0.5,Qt::KeepAspectRatio));
    name->setText("Name: "+generalItemPtr->getName());
    descr->setText("Description: "+generalItemPtr->getDescription());
    insDate->setText("Insertion Date: "+generalItemPtr->getInsertionDate().toString(Qt::ISODate));
    descr->setWordWrap(1);

    remove = new QPushButton(QIcon(":/icons/delete.png"),"",this);
    edit = new QPushButton(QIcon(":/icons/edit.png"),"",this);
    goBack= new QPushButton(QIcon(":/icons/back.png"),"",this);


    topVLayout->addWidget(name);
    topVLayout->addWidget(type,0,Qt::AlignLeft);
    topVLayout->addStretch();

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(edit);
    buttonsLayout->addWidget(remove);

    topVLayout->addLayout(buttonsLayout,Qt::AlignRight);

    innerHLayout->addWidget(goBack,0,Qt::AlignTop);
    innerHLayout->addWidget(image);
    innerHLayout->addLayout(topVLayout);

    outerVLayout->addLayout(innerHLayout);
    outerVLayout->addWidget(insDate);
    outerVLayout->addWidget(descr);
    outerVLayout->addStretch();

    connect(remove,&QPushButton::clicked,this,[this]{removeClicked(generalItemPtr);});
    connect(edit,&QPushButton::clicked,this,[this]{editClicked(generalItemPtr);});
    connect(goBack,&QPushButton::clicked,this,&generalItemDetail::goBackClicked);

}
