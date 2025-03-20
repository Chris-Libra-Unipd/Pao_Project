#ifndef BODYWIDGET_H
#define BODYWIDGET_H

#include <QWidget>
#include "sidebar.h"
#include "showlistWidget.h"
#include <QStackedWidget>
#include <QHBoxLayout>
#include "addeditvisitor.h"
#include "detailvisitor.h"
#include "mediaplayervisitor.h"
#include "collection.h"

class body: public  QWidget{
    Q_OBJECT
private:
    collection* ICollection;
    showListWidget* itemsList;
    classEditor* itemEditor;
    classDetail* itemDetails;
    classPlayer* itemPlayer;
    QStackedWidget* stack;
    sideBar* sideBarW;
    QHBoxLayout* layout;
public:
    body(collection* coll,QWidget* parent = nullptr);

public slots:
    void showFilterResult(filter* filt);
    void showSearchResult(const QString& keyword);
    void showAll();

    void detailView(item* i);
    void editView(item* i);
    void playView(item* i);

    void removeItem(item* i);
    void createItem(item* i);
    void addItem();

    void updateItemsList();

signals:
    void modified();
};

#endif // BODYWIDGET_H
