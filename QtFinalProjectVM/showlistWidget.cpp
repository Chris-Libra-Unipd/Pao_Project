#include "showlistWidget.h"
#include "book.h"
#include "movie.h"
#include "song.h"
#include "generalitem.h"

showListWidget::showListWidget(const QVector<item*>& itVec,QWidget* parent): QWidget(parent),
    outerVLayout(new QVBoxLayout(this)),
    innerHLayout(new QHBoxLayout()),
    listLayout(new QVBoxLayout()),
    scrollList(new QScrollArea(this)),
    itemsBox(new QWidget()),
    counter(new QLabel(this)),
    addItemCombo(new QComboBox(this))

{
    scrollList->setWidget(itemsBox);
    for(item* it : itVec){
        showedItems.push_back(it);
        previewVisitor visitor;
        it->accept(visitor);
        classPreview* newW = visitor.getWidget();
        listLayout->addWidget(newW);
        //for each internal widget forwards the signals so that the body widget can change state
        connect(newW,&classPreview::sendRemoveRequest, this, &showListWidget::forwardRemoveRequest);
        connect(newW,&classPreview::sendDetailsRequest, this, &showListWidget::forwardDetailsRequest);
    }
    listLayout->addStretch();
    itemsBox->setLayout(listLayout);
    listLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    addItemCombo->addItem(QIcon(":/icons/add.png"),"Add Item");
    addItemCombo->addItem(QIcon(":/icons/book.png"),"Book");
    addItemCombo->addItem(QIcon(":/icons/video.png"),"Movie");
    addItemCombo->addItem(QIcon(":/icons/music.png"),"Song");
    addItemCombo->addItem(QIcon(":/icons/box.png"),"General Item");

    counter->setText(QString::number(itVec.size())+" elements");

    innerHLayout->addWidget(counter,0,Qt::AlignLeft);
    innerHLayout->addWidget(addItemCombo,0,Qt::AlignRight);

    outerVLayout->addWidget(scrollList);
    outerVLayout->addLayout(innerHLayout);

    scrollList->setWidgetResizable(1);
    scrollList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    setMinimumWidth(itemsBox->width());

    connect(addItemCombo,&QComboBox::currentTextChanged,this,[this]{
        if(addItemCombo->currentText() != "Add Item"){
            if(addItemCombo->currentText() == "Book")
                emit sendCreationRequest(new book());
            else if(addItemCombo->currentText() == "Movie")
                emit sendCreationRequest(new movie());
            else if(addItemCombo->currentText() == "Song")
                emit sendCreationRequest(new song());
            else if(addItemCombo->currentText() == "General Item")
                emit sendCreationRequest(new generalItem());
        }
    });
}



