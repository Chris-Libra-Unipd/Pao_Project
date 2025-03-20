#include "fullwindowWidget.h"


fullWindow::fullWindow(QWidget* parent) : QMainWindow(parent),
    changesFlag(0),
    itemsColl(new collection()),
    container(new QWidget(this)),
    layout(new QVBoxLayout(container)),
    bodyW(new body(itemsColl,container)),
    toolB(new toolBar(itemsColl,container))
{
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);

    layout->addWidget(toolB);
    layout->addWidget(bodyW);
    setCentralWidget(container);

    setGeometry(50,50,800,500);
    connect(toolB,&toolBar::collectionChanged,bodyW, &body::showAll);
    connect(toolB,&toolBar::collectionSaved,this, [this]{changesFlag = 0;});
    connect(bodyW, &body::modified, this, [this]{changesFlag = 1;});

    QFile* f = new QFile(":/stylesheet.css");
    if(!f->open(QIODevice::ReadOnly))
        qWarning("Couldn't open stylesheet\n");
    setStyleSheet(f->readAll());
    f->close();
    delete f;
}

void fullWindow::closeEvent(QCloseEvent* event){
    if(changesFlag)
        toolB->saveDialog(itemsColl);
    event->accept();
}



