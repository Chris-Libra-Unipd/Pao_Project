#ifndef SHOWLISTWIDGET_H
#define SHOWLISTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "item.h"
#include <QComboBox>
#include <QVector>
#include <QScrollArea>
#include "previewvisitor.h"

class showListWidget : public  QWidget{
    Q_OBJECT
private:
    QVBoxLayout* outerVLayout;
    QHBoxLayout* innerHLayout;
    QVBoxLayout* listLayout;
    QVector<item*> showedItems;
    QScrollArea* scrollList;
    QWidget* itemsBox;
    QLabel* counter;
    QComboBox* addItemCombo;
public:
    showListWidget(const QVector<item*>& itVec,QWidget* parent = nullptr);

signals:
    void forwardRemoveRequest(item* i);
    void forwardDetailsRequest(item* i);
    void sendCreationRequest(item* i);
};
#endif // SHOWLISTWIDGET_H
