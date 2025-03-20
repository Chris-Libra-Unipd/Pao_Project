#include "toolbarWidget.h"

toolBar::toolBar(collection* coll,QWidget* parent): QWidget(parent),
ICollection(coll),
saveAs(new QPushButton(QIcon(":/icons/save.png"),"Save as",this)),
newCollection(new QPushButton(QIcon(":/icons/new.png"),"New Collection",this)),
open(new QPushButton(QIcon(":/icons/open.png"),"Open",this)),
layout(new QHBoxLayout(this)),
newCollShortcut(new QShortcut(QKeySequence("Ctrl+N"),this)),
saveCollShortcut(new QShortcut(QKeySequence("Ctrl+S"),this)),
openCollShortcut(new QShortcut(QKeySequence("Ctrl+O"),this))
{

    layout->addWidget(saveAs,0);
    layout->addWidget(open,0);
    layout->addWidget(newCollection,0);
    layout->addStretch();

    connect(saveAs,&QPushButton::clicked,this,&toolBar::saveColl);
    connect(open,&QPushButton::clicked,this,&toolBar::openColl);
    connect(newCollection,&QPushButton::clicked, this,&toolBar::createColl);

    //shortcuts
    connect(saveCollShortcut, &QShortcut::activated,this,&toolBar::saveColl);
    connect(openCollShortcut, &QShortcut::activated,this,&toolBar::openColl);
    connect(newCollShortcut, &QShortcut::activated, this,&toolBar::createColl);
}

void toolBar::saveDialog(collection* coll){
    QDialog dialog;
    QLabel message("Changes hasn't been saved!");
    QPushButton discard("Discard changes",&dialog);
    QPushButton saveAs("Save as",&dialog);
    QVBoxLayout layout(&dialog);
    layout.addWidget(&message);
    QHBoxLayout hLayout;
    hLayout.addWidget(&discard);
    hLayout.addWidget(&saveAs);
    layout.addLayout(&hLayout);

    connect(&saveAs,&QPushButton::clicked,&dialog, &QDialog::accept);
    connect(&discard,&QPushButton::clicked,&dialog, &QDialog::reject);
    dialog.exec();

    if(dialog.result() == 1)
        coll->saveCollectionAs();
}

void toolBar::saveColl(){ICollection->saveCollectionAs(); emit collectionSaved();}

void toolBar::openColl(){ICollection->loadCollection(); emit collectionChanged();}

void toolBar::createColl(){
    ICollection->clearAll();
    emit collectionChanged();
}


//for the stylesheet
void toolBar::paintEvent(QPaintEvent * event){
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
