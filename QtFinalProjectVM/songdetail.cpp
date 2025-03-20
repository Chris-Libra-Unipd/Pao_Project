#include "songdetail.h"

songDetail::songDetail(song* songPar,QWidget* parent): classDetail(parent),
    songPtr(songPar),
    topVLayout(new QVBoxLayout()),
    outerVLayout(new QVBoxLayout(this)),
    innerHLayout(new QHBoxLayout()),
    type(new QPushButton(QIcon(":/icons/music.png"),"",this)),
    descr(new QLabel(this)),
    insDate(new QLabel(this)),
    genre(new QLabel(this)),
    title(new QLabel(this)),
    pubDate(new QLabel(this)),
    size(new QLabel(this)),
    artist(new QLabel(this)),
    duration(new QLabel(this)),
    image(new QLabel(this)),
    play(new QPushButton(QIcon(":/icons/play.png"),"",this))
{
    //body
    image->setPixmap(QPixmap(songPtr->getImagePath()).scaled(this->width()*0.5,this->width()*0.5,Qt::KeepAspectRatio));
    title->setText("Title: "+songPtr->getTitle());
    pubDate->setText("Publication Date: "+songPtr->getPublicationDate().toString(Qt::ISODate));
    insDate->setText("Insertion Date: "+songPtr->getInsertionDate().toString(Qt::ISODate));
    duration->setText("Duration: "+songPtr->getDuration().toString());

    artist->setText("Artist: "+songPtr->getArtist());
    size->setText("Size: "+ QString::number(songPtr->getSize())+" MB");
    genre->setText("Genre: "+songPtr->getGenre());
    descr->setText("Description: "+songPtr->getDescription());
    descr->setWordWrap(1);

    remove = new QPushButton(QIcon(":/icons/delete.png"),"",this);
    edit = new QPushButton(QIcon(":/icons/edit.png"),"",this);
    goBack= new QPushButton(QIcon(":/icons/back.png"),"",this);

    topVLayout->addWidget(title);
    topVLayout->addWidget(pubDate);
    topVLayout->addWidget(genre);
    topVLayout->addWidget(duration);
    topVLayout->addWidget(artist);
    topVLayout->addWidget(type,0,Qt::AlignLeft);
    topVLayout->addStretch();

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(play);
    buttonsLayout->addWidget(edit);
    buttonsLayout->addWidget(remove);

    topVLayout->addLayout(buttonsLayout,Qt::AlignRight);

    innerHLayout->addWidget(goBack,0,Qt::AlignTop);
    innerHLayout->addWidget(image);
    innerHLayout->addLayout(topVLayout);

    outerVLayout->addLayout(innerHLayout);
    outerVLayout->addWidget(insDate);
    outerVLayout->addWidget(size);
    outerVLayout->addWidget(descr);
    outerVLayout->addStretch();

    connect(remove,&QPushButton::clicked,this,[this]{removeClicked(songPtr);});
    connect(edit,&QPushButton::clicked,this,[this]{editClicked(songPtr);});
    connect(goBack,&QPushButton::clicked,this,&songDetail::goBackClicked);
    connect(play,&QPushButton::clicked,this,[this]{
        if(songPtr->getMediaPath().isEmpty()){
            QMessageBox err;
            err.setWindowTitle("Error");
            err.setText("No audio path is provided!");
            err.exec();
        }
        else
            playClicked(songPtr);
    });
}

