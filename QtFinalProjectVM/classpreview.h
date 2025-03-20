#ifndef CLASSPREVIEW_H
#define CLASSPREVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>

class item;

class classPreview : public QWidget{
    Q_OBJECT
protected:
    QPushButton* remove;
    QPushButton* details;
public:
    virtual ~classPreview() = 0;
    classPreview(QWidget* parent = nullptr);

signals:
    void sendRemoveRequest(item* i);
    void sendDetailsRequest(item* i);
    void sendEditRequest(item* i);
};


#endif // CLASSPREVIEW_H
