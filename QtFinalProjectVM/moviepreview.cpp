#include "moviepreview.h"


moviePreview::moviePreview(movie* moviePar,QWidget* parent): classPreview(parent),
    moviePtr(moviePar),
    innerVLayout(new QVBoxLayout()),
    outerHLayout(new QHBoxLayout(this)),
    type(new QPushButton(QIcon(":/icons/video.png"),"",this)),
    title(new QLabel(this)),
    genre(new QLabel(this)),
    director(new QLabel(this)),
    pubDate(new QLabel(this)),
    image(new QLabel(this))
{
    //body
    image->setPixmap(QPixmap(moviePtr->getImagePath()).scaled(this->width()*0.2,this->width()*0.2,Qt::KeepAspectRatio));
    title->setText("Title: "+moviePtr->getTitle());
    genre->setText("Genre: "+moviePtr->getGenre());
    director->setText("Director: "+moviePtr->getDirector());
    pubDate->setText("Publication: "+moviePtr->getPublicationDate().toString(Qt::ISODate));

    remove = new QPushButton(QIcon(":/icons/delete.png"),"",this);
    details = new QPushButton(QIcon(":/icons/info.png"),"",this);

    innerVLayout->addWidget(title);
    innerVLayout->addWidget(genre);
    innerVLayout->addWidget(director);
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

    connect(remove,&QPushButton::clicked,this,[this]{emit sendRemoveRequest(moviePtr);});
    connect(details,&QPushButton::clicked,this,[this]{emit sendDetailsRequest(moviePtr);});
}


