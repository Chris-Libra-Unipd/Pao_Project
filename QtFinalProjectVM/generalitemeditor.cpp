#include "generalitemeditor.h"

generalItemEditor::generalItemEditor(generalItem* generalItemPar, bool flag, QWidget* parent):classEditor(parent),
    generalItemPtr(generalItemPar),
    Glayout(new QGridLayout()),
    layout(new QVBoxLayout(this)),
    descr(new QLabel("Description: ",this)),
    insDate(new QLabel("Insertion Date: ",this)),
    imgPath(new QLabel("Image Path*: ",this)),
    name(new QLabel("Name*: ",this)),
    image(new QLabel(this)),
    descrInp(new QTextEdit(this)),
    insDateInp(new QDateTimeEdit(QDate::currentDate(),this)),
    imgPathInp(new QLineEdit(this)),
    nameInp(new QLineEdit(this)),
    findPath(new QPushButton("Find path",this)),
    edit(flag)

{
    //body
    header=new QLabel("General Item creation",this);
    confirm=new QPushButton("Confirm",this);
    cancel=new QPushButton("Cancel",this);
    header->setAlignment(Qt::AlignCenter);

    insDateInp->setDisplayFormat("dd.MM.yyyy");

    imgPathInp->setText(":/media/noImg.jpg");


    //if edit flag = 1 fill the input lines with the book's fields
    if(edit){
        header->setText("General Item editing");
        descrInp->setText(generalItemPtr->getDescription());
        insDateInp->setDate(generalItemPtr->getInsertionDate());
        nameInp->setText(generalItemPtr->getName());
        imgPathInp->setText(generalItemPtr->getImagePath());
        if(!(imgPathInp->text().isEmpty()))
            image->setPixmap(QPixmap(generalItemPtr->getImagePath()).scaled(this->width()*0.2,this->width()*0.2,Qt::KeepAspectRatio));
    }

    //populate the layout
    Glayout->addWidget(name,0,0,Qt::AlignRight);
    Glayout->addWidget(nameInp,0,1);
    Glayout->addWidget(insDate,5,0,Qt::AlignRight);
    Glayout->addWidget(insDateInp,5,1);
    Glayout->addWidget(imgPath,6,0,Qt::AlignRight);
    Glayout->addWidget(imgPathInp,6,1);
    Glayout->addWidget(findPath,6,2);
    Glayout->addWidget(descr,8,0,Qt::AlignRight | Qt::AlignTop);
    Glayout->addWidget(descrInp,8,1);

    Glayout->addWidget(image,0,3);
    Glayout->addWidget(confirm,9,3,Qt::AlignBottom);
    Glayout->addWidget(cancel,9,2,Qt::AlignBottom);

    layout->addWidget(header);
    layout->addLayout(Glayout);

    QObject::connect(findPath, &QPushButton::clicked,this, &generalItemEditor::updateImage);

    QObject::connect(confirm, &QPushButton::clicked,this, &generalItemEditor::updateFields);
    QObject::connect(cancel, &QPushButton::clicked,this, &classEditor::rejected);
}

void generalItemEditor::updateFields(){
    if(nameInp->text().isEmpty()|| imgPathInp->text().isEmpty()){
        QMessageBox err;
        err.setWindowTitle("Error");
        err.setText("Some necessary fields are empty!");
        err.exec();
    }
    else{
        generalItemPtr->setDescription(descrInp->toPlainText());
        generalItemPtr->setInsertionDate(insDateInp->date());
        generalItemPtr->setName(nameInp->text());
        generalItemPtr->setImagePath(imgPathInp->text());
        emit classEditor::accepted();
    }
}

void generalItemEditor::updateImage(){
    imgPathInp->setText(QFileDialog::getOpenFileName(this,"Find file","","Image Files (*.png *.jpg *.jpeg"));
    image->setPixmap(QPixmap(imgPathInp->text()).scaled(this->width()*0.2,this->width()*0.2,Qt::KeepAspectRatio));
}
item* generalItemEditor::getItem() const{
    return generalItemPtr;
}
