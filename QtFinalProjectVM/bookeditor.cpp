#include "bookeditor.h"


bookEditor::bookEditor(book* bookPar, bool flag, QWidget* parent): classEditor(parent),
bookPtr(bookPar),
Glayout(new QGridLayout()),
layout(new QVBoxLayout(this)),
descr(new QLabel("Description: ",this)),
pubDate(new QLabel("Publication Date: ",this)),
genre(new QLabel("Genre: ",this)),
title(new QLabel("Title*: ",this)),
author(new QLabel("Author*: ",this)),
pages(new QLabel("Pages*: ",this)),
insDate(new QLabel("Insertion Date: ",this)),
imgPath(new QLabel("Image Path*: ",this)),
image(new QLabel(this)),
descrInp(new QTextEdit(this)),
pubDateInp(new QDateTimeEdit(this)),
insDateInp(new QDateTimeEdit(QDate::currentDate(),this)),
genreInp(new QLineEdit(this)),
titleInp(new QLineEdit(this)),
authorInp(new QLineEdit(this)),
pagesInp(new QLineEdit(this)),
imgPathInp(new QLineEdit(this)),
findPath(new QPushButton("Find path",this)),
edit(flag)
{
    //constructor body
    header=new QLabel("Book creation",this);
    confirm=new QPushButton("Confirm",this);
    cancel=new QPushButton("Cancel",this);
    header->setAlignment(Qt::AlignCenter);

    insDateInp->setDisplayFormat("dd.MM.yyyy");
    pubDateInp->setDisplayFormat("dd.MM.yyyy");

    imgPathInp->setText(":/media/noImg.jpg");

    //if edit flag = 1 fill the input lines with the book's fields
    if(edit){
        header->setText("Book editing");
        descrInp->setText(bookPtr->getDescription());
        pubDateInp->setDate(bookPtr->getPublicationDate());
        insDateInp->setDate(bookPtr->getInsertionDate());
        genreInp->setText(bookPtr->getGenre());
        titleInp->setText(bookPtr->getTitle());
        authorInp->setText(bookPtr->getAuthor());
        pagesInp->setText(QString::number(bookPtr->getPages()));
        imgPathInp->setText(bookPtr->getImagePath());
        if(!(imgPathInp->text().isEmpty()))
            image->setPixmap(QPixmap(bookPtr->getImagePath()).scaled(this->width()*0.2,this->width()*0.2,Qt::KeepAspectRatio));
    }
    //populate the layout
    Glayout->addWidget(title,0,0,Qt::AlignRight);
    Glayout->addWidget(titleInp,0,1);
    Glayout->addWidget(author,1,0,Qt::AlignRight);
    Glayout->addWidget(authorInp,1,1);
    Glayout->addWidget(pubDate,2,0,Qt::AlignRight);
    Glayout->addWidget(pubDateInp,2,1);
    Glayout->addWidget(genre,3,0,Qt::AlignRight);
    Glayout->addWidget(genreInp,3,1);
    Glayout->addWidget(pages,4,0,Qt::AlignRight);
    Glayout->addWidget(pagesInp,4,1);
    Glayout->addWidget(insDate,5,0,Qt::AlignRight);
    Glayout->addWidget(insDateInp,5,1);
    Glayout->addWidget(imgPath,6,0,Qt::AlignRight);
    Glayout->addWidget(imgPathInp,6,1);
    Glayout->addWidget(findPath,6,2);
    Glayout->addWidget(descr,7,0,Qt::AlignTop | Qt::AlignRight);
    Glayout->addWidget(descrInp,7,1);

    Glayout->addWidget(image,0,3);
    Glayout->addWidget(confirm,7,3,Qt::AlignBottom);
    Glayout->addWidget(cancel,7,2,Qt::AlignBottom);

    layout->addWidget(header);
    layout->addLayout(Glayout);

    //change image slot
    QObject::connect(findPath, &QPushButton::clicked,this, &bookEditor::updateImage);

    //update the book's fields
    QObject::connect(confirm, &QPushButton::clicked,this, &bookEditor::updateFields);
    QObject::connect(cancel, &QPushButton::clicked,this, &classEditor::rejected);
}

void bookEditor::updateFields(){
    if(titleInp->text().isEmpty() || pagesInp->text().isEmpty() || authorInp->text().isEmpty() || imgPathInp->text().isEmpty()){
        QMessageBox err;
        err.setWindowTitle("Error");
        err.setText("Some necessary fields are empty!");
        err.exec();
    }
    else if(pagesInp->text().toUInt() == 0){//conversion failed
        QMessageBox err;
        err.setWindowTitle("Error");
        err.setText("Number of pages is not valid!");
        err.exec();
    }
    else{
        bookPtr->setDescription(descrInp->toPlainText());
        bookPtr->setPublicationDate(pubDateInp->date());
        bookPtr->setInsertionDate(insDateInp->date());
        bookPtr->setGenre(genreInp->text());
        bookPtr->setTitle(titleInp->text());
        bookPtr->setAuthor(authorInp->text());
        bookPtr->setPages(pagesInp->text().toUInt());
        bookPtr->setImagePath(imgPathInp->text());
        emit classEditor::accepted();
    }
}

void bookEditor::updateImage(){
    imgPathInp->setText(QFileDialog::getOpenFileName(this,"Find file","","Image Files (*.png *.jpg *.jpeg"));
    image->setPixmap(QPixmap(imgPathInp->text()).scaled(this->width()*0.2,this->width()*0.2,Qt::KeepAspectRatio));
}


item* bookEditor::getItem() const{
    return bookPtr;
}

