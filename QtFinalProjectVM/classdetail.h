#ifndef CLASSDETAIL_H
#define CLASSDETAIL_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QMessageBox>

class item;

class classDetail : public QWidget{
    Q_OBJECT
protected:
    QPushButton* remove;
    QPushButton* edit;
    QPushButton* goBack;
public:
    virtual ~classDetail() = 0;
    classDetail(QWidget* parent = nullptr);
signals:
    void editClicked(item* item);
    void removeClicked(item* item);
    void playClicked(item* item);
    void goBackClicked();
};

#endif // CLASSDETAIL_H
