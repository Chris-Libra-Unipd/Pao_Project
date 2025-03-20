#include "bodyWidget.h"

body::body(collection* coll, QWidget* parent) : QWidget(parent),
    ICollection(coll),
    itemsList(new showListWidget(ICollection->getItems(),this)),
    itemEditor(nullptr),
    itemDetails(nullptr),
    itemPlayer(nullptr),
    stack(new QStackedWidget(this)),
    sideBarW(new sideBar(this)),
    layout(new QHBoxLayout(this))
{

    stack->addWidget(itemsList);

    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);

    layout->addWidget(sideBarW,0);
    layout->addWidget(stack,1);

    connect(sideBarW, &sideBar::dimChanged,this,[this]{
        sideBarW->updateGeometry();
        itemsList->updateGeometry();
    });

    connect(sideBarW, &sideBar::searchRequest,this,&body::showSearchResult);
    connect(sideBarW, &sideBar::filterRequest,this,&body::showFilterResult);
    connect(sideBarW, &sideBar::showAllRequest,this,&body::showAll);

    //preview list connections...
    connect(itemsList, &showListWidget::forwardDetailsRequest,this,&body::detailView);
    connect(itemsList, &showListWidget::forwardRemoveRequest,this,&body::removeItem);
    connect(itemsList, &showListWidget::sendCreationRequest,this,&body::createItem);

    //delete media player if the main widget changes and itemPlayer is not the current widget
    //fixes bug: while changing widget the video was showed for fraction of a second and the audio continued to be played
    connect(stack, &QStackedWidget::currentChanged,this,[this]{
        if(itemPlayer != nullptr && stack->currentIndex() != stack->indexOf(itemPlayer)){
            stack->removeWidget(itemPlayer);
            delete itemPlayer;
            itemPlayer = nullptr;
        }
    });
}

void body::showFilterResult(filter* filt){
    stack->removeWidget(itemsList);
    delete itemsList;
    itemsList = new showListWidget(ICollection->applyFilter(*filt),this);
    delete filt;
    stack->addWidget(itemsList);
    stack->setCurrentWidget(itemsList);

    //update connections
    connect(itemsList, &showListWidget::forwardDetailsRequest,this,&body::detailView);
    connect(itemsList, &showListWidget::forwardRemoveRequest,this,&body::removeItem);
    connect(itemsList, &showListWidget::sendCreationRequest,this,&body::createItem);


}

void body::showSearchResult(const QString& keyword){
    stack->removeWidget(itemsList);
    delete itemsList;
    itemsList = new showListWidget(ICollection->makeSearch(keyword),this);
    stack->addWidget(itemsList);
    stack->setCurrentWidget(itemsList);
    //update connections
    connect(itemsList, &showListWidget::forwardDetailsRequest,this,&body::detailView);
    connect(itemsList, &showListWidget::forwardRemoveRequest,this,&body::removeItem);
    connect(itemsList, &showListWidget::sendCreationRequest,this,&body::createItem);


}

void body::showAll(){
    stack->removeWidget(itemsList);
    delete itemsList;
    itemsList = new showListWidget(ICollection->getItems(),this);
    stack->addWidget(itemsList);
    stack->setCurrentWidget(itemsList);
    //update connections
    connect(itemsList, &showListWidget::forwardDetailsRequest,this,&body::detailView);
    connect(itemsList, &showListWidget::forwardRemoveRequest,this,&body::removeItem);
    connect(itemsList, &showListWidget::sendCreationRequest,this,&body::createItem);
}

void body::detailView(item* i){
    detailVisitor* visitor = new detailVisitor();
    i->accept(*visitor);
    if(itemDetails){
        stack->removeWidget(itemDetails);
        delete itemDetails;
    }
    itemDetails = visitor->getWidget();
    stack->addWidget(itemDetails);
    stack->setCurrentWidget(itemDetails);
    delete visitor;

    connect(itemDetails, &classDetail::editClicked,this,&body::editView);
    connect(itemDetails, &classDetail::removeClicked,this,&body::removeItem);
    connect(itemDetails, &classDetail::playClicked,this,&body::playView);
    connect(itemDetails, &classDetail::goBackClicked,this,[this]{
        updateItemsList();
        stack->setCurrentWidget(itemsList);
    });

}

void body::editView(item* i){
    addEditVisitor* visitor = new addEditVisitor();
    visitor->setEditFlag(1);
    i->accept(*visitor);
    if(itemEditor){
        stack->removeWidget(itemEditor);
        delete itemEditor;
    }
    itemEditor = visitor->getWidget();
    stack->addWidget(itemEditor);
    stack->setCurrentWidget(itemEditor);
    delete visitor;

    connect(itemEditor, &classEditor::accepted,this,[this,i]{detailView(i);});
    connect(itemEditor, &classEditor::rejected,this,[this,i]{detailView(i);});

    connect(itemEditor, &classEditor::accepted,this,&body::modified);
}

void body::playView(item* i){
    mediaPlayerVisitor* visitor = new mediaPlayerVisitor();
    i->accept(*visitor);
    if(itemPlayer){
        stack->removeWidget(itemPlayer);
        delete itemPlayer;
    }
    itemPlayer = visitor->getWidget();
    stack->addWidget(itemPlayer);
    stack->setCurrentWidget(itemPlayer);
    delete visitor;
    itemPlayer->play();
    connect(itemPlayer, &classPlayer::goBackClicked, this, [this]{
        updateItemsList();
        stack->setCurrentWidget(itemDetails);});
}

void body::removeItem(item* i){
    emit modified();
    ICollection->removeItem(i);
    showAll();
}

void body::updateItemsList(){
    stack->removeWidget(itemsList);
    delete itemsList;
    itemsList = new showListWidget(ICollection->getItems(),this);
    //update connections
    connect(itemsList, &showListWidget::forwardDetailsRequest,this,&body::detailView);
    connect(itemsList, &showListWidget::forwardRemoveRequest,this,&body::removeItem);
    connect(itemsList, &showListWidget::sendCreationRequest,this,&body::createItem);

    stack->addWidget(itemsList);
}

void body::createItem(item* i){
    addEditVisitor* visitor = new addEditVisitor();
    visitor->setEditFlag(0);
    i->accept(*visitor);
    if(itemEditor){
        stack->removeWidget(itemEditor);
        delete itemEditor;
    }
    itemEditor = visitor->getWidget();
    stack->addWidget(itemEditor);
    stack->setCurrentWidget(itemEditor);
    delete visitor;

    connect(itemEditor, &classEditor::rejected,this,&body::showAll);
    connect(itemEditor, &classEditor::accepted,this,&body::addItem);
}

void body::addItem(){
    emit modified();
    item* newI = itemEditor->getItem();
    ICollection->addItem(newI);
    updateItemsList();
    detailView(newI);
}



