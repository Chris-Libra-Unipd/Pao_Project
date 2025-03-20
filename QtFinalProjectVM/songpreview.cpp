#include "songpreview.h"

songPreview::songPreview(song* songPar,QWidget* parent): classPreview(parent),
    songPtr(songPar),
    innerVLayout(new QVBoxLayout()),
    outerHLayout(new QHBoxLayout(this)),
    type(new QPushButton(QIcon(":/icons/music.png"),"",this)),
    title(new QLabel(this)),
    genre(new QLabel(this)),
    artist(new QLabel(this)),
    pubDate(new QLabel(this)),
    image(new QLabel(this))
{
    //body
    image->setPixmap(QPixmap(songPtr->getImagePath()).scaled(this->width()*0.2,this->width()*0.2,Qt::KeepAspectRatio));
    title->setText("Title: "+songPtr->getTitle());
    genre->setText("Genre: "+ songPtr->getGenre());
    pubDate->setText("Publication: "+songPtr->getPublicationDate().toString(Qt::ISODate));
    artist->setText("Artist: "+ songPtr->getArtist());

    remove = new QPushButton(QIcon(":/icons/delete.png"),"",this);
    details = new QPushButton(QIcon(":/icons/info.png"),"",this);

    innerVLayout->addWidget(title);
    innerVLayout->addWidget(genre);
    innerVLayout->addWidget(artist);
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

    connect(remove,&QPushButton::clicked,this,[this]{emit sendRemoveRequest(songPtr);});
    connect(details,&QPushButton::clicked,this,[this]{emit sendDetailsRequest(songPtr);});
}
