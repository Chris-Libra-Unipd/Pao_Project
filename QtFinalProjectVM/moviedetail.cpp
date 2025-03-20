#include "moviedetail.h"
#include <QVector>

movieDetail::movieDetail(movie* moviePar,QWidget* parent): classDetail(parent),
    moviePtr(moviePar),
    topVLayout(new QVBoxLayout()),
    outerVLayout(new QVBoxLayout(this)),
    innerHLayout(new QHBoxLayout()),
    type(new QPushButton(QIcon(":/icons/video.png"),"",this)),
    descr(new QLabel(this)),
    insDate(new QLabel(this)),
    genre(new QLabel(this)),
    title(new QLabel(this)),
    pubDate(new QLabel(this)),
    size(new QLabel(this)),
    director(new QLabel(this)),
    actors(new QLabel(this)),
    duration(new QLabel(this)),
    image(new QLabel(this)),
    play(new QPushButton(QIcon(":/icons/play.png"),"",this))
{
    //body
    image->setPixmap(QPixmap(moviePtr->getImagePath()).scaled(this->width()*0.5,this->width()*0.5,Qt::KeepAspectRatio));
    title->setText("Title: "+moviePtr->getTitle());
    pubDate->setText("Publication Date: "+moviePtr->getPublicationDate().toString(Qt::ISODate));
    insDate->setText("Insertion Date: "+moviePtr->getInsertionDate().toString(Qt::ISODate));
    duration->setText("Duration: "+moviePtr->getDuration().toString());
    QString cast;
    for(QString& actor: moviePtr->getCast())
        cast += actor + ", ";
    actors->setText("Cast: "+cast);
    director->setText("Director: "+moviePtr->getDirector());
    size->setText("Size: "+ QString::number(moviePtr->getSize())+" MB");
    genre->setText("Genre: "+moviePtr->getGenre());
    descr->setText("Description: "+moviePtr->getDescription());
    descr->setWordWrap(1);

    remove = new QPushButton(QIcon(":/icons/delete.png"),"",this);
    edit = new QPushButton(QIcon(":/icons/edit.png"),"",this);
    goBack= new QPushButton(QIcon(":/icons/back.png"),"",this);

    topVLayout->addWidget(title);
    topVLayout->addWidget(pubDate);
    topVLayout->addWidget(genre);
    topVLayout->addWidget(duration);
    topVLayout->addWidget(director);
    topVLayout->addWidget(actors);
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

    connect(remove,&QPushButton::clicked,this,[this]{removeClicked(moviePtr);});
    connect(edit,&QPushButton::clicked,this,[this]{editClicked(moviePtr);});
    connect(goBack,&QPushButton::clicked,this,&movieDetail::goBackClicked);

    connect(play,&QPushButton::clicked,this,[this]{
        if(moviePtr->getMediaPath().isEmpty()){
            QMessageBox err;
            err.setWindowTitle("Error");
            err.setText("No video path is provided!");
            err.exec();
        }
        else
            playClicked(moviePtr);
    });
}
