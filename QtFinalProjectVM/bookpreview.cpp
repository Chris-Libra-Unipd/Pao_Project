#include "bookpreview.h"

bookPreview::bookPreview(book* bookPar,QWidget* parent): classPreview(parent),
    bookPtr(bookPar),
    innerVLayout(new QVBoxLayout()),
    outerHLayout(new QHBoxLayout(this)),
    title(new QLabel(this)),
    genre(new QLabel(this)),
    author(new QLabel(this)),
    pubDate(new QLabel(this)),
    image(new QLabel(this)),
    type(new QPushButton(QIcon(":/icons/book.png"),"",this))
{
    //body
    image->setPixmap(QPixmap(bookPtr->getImagePath()).scaled(this->width()*0.2,this->width()*0.2,Qt::KeepAspectRatio));
    title->setText("Title: "+bookPtr->getTitle());
    author->setText("Author: "+bookPtr->getAuthor());
    genre->setText("Genre: "+bookPtr->getGenre());
    pubDate->setText("Publication: "+bookPtr->getPublicationDate().toString(Qt::ISODate));

    remove = new QPushButton(QIcon(":/icons/delete.png"),"",this);
    details = new QPushButton(QIcon(":/icons/info.png"),"",this);

    innerVLayout->addWidget(title);
    innerVLayout->addWidget(genre);
    innerVLayout->addWidget(author);
    innerVLayout->addWidget(pubDate);
    innerVLayout->addWidget(type,0,Qt::AlignLeft);
    innerVLayout->addStretch();

    outerHLayout->addWidget(image);
    outerHLayout->addLayout(innerVLayout);
    outerHLayout->addStretch();
    outerHLayout->addWidget(details,0,Qt::AlignBottom);
    outerHLayout->addWidget(remove,0,Qt::AlignBottom);

    setMinimumHeight(sizeHint().height());
    setMaximumHeight(sizeHint().height());

    connect(remove,&QPushButton::clicked,this,[this]{emit sendRemoveRequest(bookPtr);});
    connect(details,&QPushButton::clicked,this,[this]{emit sendDetailsRequest(bookPtr);});
}
