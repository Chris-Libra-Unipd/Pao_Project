#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "filterwidget.h"
#include <QVBoxLayout>
#include <QIcon>
#include <QHBoxLayout>
#include <QPainter>
#include <QStyleOption>
#include <QPaintEvent>

class sideBar : public QWidget{
    Q_OBJECT
private:
    QLineEdit* searchBar;
    QPushButton* searchButton;
    filterWidget* filterSection;
    QPushButton* showAll;

    QVBoxLayout* outerLayout;
    QHBoxLayout* innerLayout;
public:
    sideBar(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent * event) override;

signals:
    void dimChanged();
    void searchRequest(const QString& keyword);
    void filterRequest(filter* filter);
    void showAllRequest();
};

#endif // SIDEBAR_H
