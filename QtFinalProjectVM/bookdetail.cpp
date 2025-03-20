#include "bookdetail.h"
#include <QIcon>

bookDetail::bookDetail(book* bookPar,QWidget* parent): classDetail(parent),
    bookPtr(bookPar),
    topVLayout(new QVBoxLayout()),
    outerVLayout(new QVBoxLayout(this)),
    innerHLayout(new QHBoxLayout()),
    descr(new QLabel(this)),
    insDate(new QLabel(this)),
    genre(new QLabel(this)),
    title(new QLabel(this)),
    pubDate(new QLabel(this)),
    author(new QLabel(this)),
    pages(new QLabel(this)),
    type(new QPushButton(QIcon(":/icons/book.png"),"",this)),
    image(new QLabel(this))
{
    //body
    image->setPixmap(QPixmap(bookPtr->getImagePath()).scaled(this->width()*0.5,this->width()*0.5,Qt::KeepAspectRatio));
    title->setText("Title: "+bookPtr->getTitle());
    pubDate->setText("Publication Date: "+bookPtr->getPublicationDate().toString(Qt::ISODate));
    insDate->setText("Insertion Date: "+bookPtr->getInsertionDate().toString(Qt::ISODate));
    pages->setText("Pages: "+QString::number(bookPtr->getPages()));
    author->setText("Artist: "+bookPtr->getAuthor());
    genre->setText("Genre: "+bookPtr->getGenre());
    descr->setText("Description :"+bookPtr->getDescription());
    descr->setWordWrap(1);

    remove = new QPushButton(QIcon(":/icons/delete.png"),"",this);
    edit = new QPushButton(QIcon(":/icons/edit.png"),"",this);
    goBack= new QPushButton(QIcon(":/icons/back.png"),"",this);

    topVLayout->addWidget(title);
    topVLayout->addWidget(pubDate);
    topVLayout->addWidget(genre);
    topVLayout->addWidget(author);
    topVLayout->addWidget(type,0,Qt::AlignLeft);
    topVLayout->addStretch();

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(edit);
    buttonsLayout->addWidget(remove);

    topVLayout->addLayout(buttonsLayout,Qt::AlignRight);

    innerHLayout->addWidget(goBack,0,Qt::AlignTop);
    innerHLayout->addWidget(image);
    innerHLayout->addLayout(topVLayout);

    outerVLayout->addLayout(innerHLayout);
    outerVLayout->addWidget(insDate);
    outerVLayout->addWidget(pages);
    outerVLayout->addWidget(descr);
    outerVLayout->addStretch();

    connect(remove,&QPushButton::clicked,this,[this]{removeClicked(bookPtr);});
    connect(edit,&QPushButton::clicked,this,[this]{editClicked(bookPtr);});
    connect(goBack,&QPushButton::clicked,this,&bookDetail::goBackClicked);
}
