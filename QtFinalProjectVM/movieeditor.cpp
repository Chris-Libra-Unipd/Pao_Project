#include "movieeditor.h"
#include <QVector>



movieEditor::movieEditor(movie* moviePar, bool flag, QWidget* parent):classEditor(parent),
    moviePtr(moviePar),
    Glayout(new QGridLayout()),
    layout(new QVBoxLayout(this)),
    descr(new QLabel("Description: ",this)),
    insDate(new QLabel("Insertion Date: ",this)),
    imgPath(new QLabel("Image Path*: ",this)),
    genre(new QLabel("Genre: ",this)),
    title(new QLabel("Title*: ",this)),
    pubDate(new QLabel("Publication Date: ",this)),
    mediaPath(new QLabel("Video Path",this)),
    size(new QLabel("Size",this)),
    director(new QLabel("Director",this)),
    actors(new QLabel("Cast",this)),
    duration(new QLabel("Duration",this)),
    image(new QLabel(this)),
    descrInp(new QTextEdit(this)),
    insDateInp(new QDateTimeEdit(QDate::currentDate(),this)),
    imgPathInp(new QLineEdit(this)),
    genreInp(new QLineEdit(this)),
    titleInp(new QLineEdit(this)),
    pubDateInp(new QDateTimeEdit(this)),
    mediaPathInp(new QLineEdit(this)),
    sizeInp(new QLineEdit(this)),
    directorInp(new QLineEdit(this)),
    actorsList(new QListWidget(this)),
    actorInp(new QLineEdit(this)),
    durInpH(new QLineEdit(this)),
    durInpM(new QLineEdit(this)),
    durInpS(new QLineEdit(this)),
    findPath(new QPushButton("Find path",this)),
    findPathMedia(new QPushButton("Find path",this)),
    addActor(new QPushButton("Add",this)),
    deleteActor(new QPushButton("Delete selected actor",this)),
    edit(flag)

{
    //body
    header=new QLabel("Movie creation",this);
    confirm=new QPushButton("Confirm",this);
    cancel=new QPushButton("Cancel",this);
    header->setAlignment(Qt::AlignCenter);

    insDateInp->setDisplayFormat("dd.MM.yyyy");
    pubDateInp->setDisplayFormat("dd.MM.yyyy");

    imgPathInp->setText(":/media/noImg.jpg");

    durInpH->setPlaceholderText("h");
    durInpM->setPlaceholderText("min");
    durInpS->setPlaceholderText("sec");
    actorInp->setPlaceholderText("new actor");


    //if edit flag = 1 fill the input lines with the book's fields
    if(edit){
        header->setText("Movie editing");
        descrInp->setText(moviePtr->getDescription());
        pubDateInp->setDate(moviePtr->getPublicationDate());
        insDateInp->setDate(moviePtr->getInsertionDate());
        genreInp->setText(moviePtr->getGenre());
        titleInp->setText(moviePtr->getTitle());
        imgPathInp->setText(moviePtr->getImagePath());
        mediaPathInp->setText(moviePtr->getMediaPath());
        if(!(imgPathInp->text().isEmpty()))
            image->setPixmap(QPixmap(moviePtr->getImagePath()).scaled(this->width()*0.2,this->width()*0.2,Qt::KeepAspectRatio));
        sizeInp->setText(QString::number(moviePtr->getSize()));
        directorInp->setText(moviePtr->getDirector());
        for(QString& act: moviePtr->getCast())
            actorsList->addItem(act);
        durInpH->setText(QString::number(moviePtr->getDuration().hour()));
        durInpM->setText(QString::number(moviePtr->getDuration().minute()));
        durInpS->setText(QString::number(moviePtr->getDuration().second()));

    }
    QHBoxLayout* intHLayout = new QHBoxLayout();
    intHLayout->addWidget(durInpH);
    intHLayout->addWidget(durInpM);
    intHLayout->addWidget(durInpS);


    QHBoxLayout* addHLayout =  new QHBoxLayout();
    addHLayout->addWidget(actorInp);
    addHLayout->addWidget(addActor);
    QVBoxLayout* intVLayout = new QVBoxLayout();
    intVLayout->addLayout(addHLayout);
    intVLayout->addWidget(deleteActor);

    Glayout->addWidget(title,0,0,Qt::AlignRight);
    Glayout->addWidget(titleInp,0,1);
    Glayout->addWidget(director,1,0,Qt::AlignRight);
    Glayout->addWidget(directorInp,1,1);
    Glayout->addWidget(pubDate,2,0,Qt::AlignRight);
    Glayout->addWidget(pubDateInp,2,1);
    Glayout->addWidget(genre,3,0,Qt::AlignRight);
    Glayout->addWidget(genreInp,3,1);
    Glayout->addWidget(actors,4,0,Qt::AlignRight | Qt::AlignTop);
    Glayout->addWidget(actorsList,4,1);
    Glayout->addLayout(intVLayout,4,2,Qt::AlignTop);
    Glayout->addWidget(duration,5,0,Qt::AlignRight);
    Glayout->addLayout(intHLayout,5,1);
    Glayout->addWidget(insDate,6,0,Qt::AlignRight);
    Glayout->addWidget(insDateInp,6,1);
    Glayout->addWidget(imgPath,7,0,Qt::AlignRight);
    Glayout->addWidget(imgPathInp,7,1);
    Glayout->addWidget(findPath,7,2);
    Glayout->addWidget(mediaPath,8,0,Qt::AlignRight);
    Glayout->addWidget(mediaPathInp,8,1);
    Glayout->addWidget(findPathMedia,8,2);
    Glayout->addWidget(descr,9,0,Qt::AlignRight | Qt::AlignTop);
    Glayout->addWidget(descrInp,9,1);
    Glayout->addWidget(size,10,0,Qt::AlignRight);
    Glayout->addWidget(sizeInp,10,1);

    Glayout->addWidget(image,0,3);
    Glayout->addWidget(confirm,10,3,Qt::AlignBottom);
    Glayout->addWidget(cancel,10,2,Qt::AlignBottom);

    layout->addWidget(header);
    layout->addLayout(Glayout);

    QObject::connect(findPath, &QPushButton::clicked,this, &movieEditor::updateImage);
    QObject::connect(findPathMedia, &QPushButton::clicked,this,&movieEditor::updateMedia);
    QObject::connect(addActor, &QPushButton::clicked,this, &movieEditor::addActorCommand);
    QObject::connect(deleteActor, &QPushButton::clicked,this, &movieEditor::deleteActorCommand);

    QObject::connect(confirm, &QPushButton::clicked,this, &movieEditor::updateFields);
    QObject::connect(cancel, &QPushButton::clicked,this, &classEditor::rejected);
}

void movieEditor::updateFields(){
    bool okH,okM,okS;
    durInpH->text().toInt(&okH);
    durInpM->text().toInt(&okM);
    durInpS->text().toInt(&okS);
    if(titleInp->text().isEmpty() || imgPathInp->text().isEmpty()){
        QMessageBox err;
        err.setWindowTitle("Error");
        err.setText("Some necessary fields are empty!");
        err.exec();
    }
    //if sizeInp is not empty and the conversion fails or
    //if at least one of the duration fields is not empty and at least one of the conversions fails
    else if((!sizeInp->text().isEmpty() && sizeInp->text().toDouble() == 0.0) ||
             ((!durInpH->text().isEmpty() || !durInpM->text().isEmpty() || !durInpS->text().isEmpty())&&(!okH || !okM || !okS))){
            QMessageBox err;
            err.setWindowTitle("Error");
            err.setText("Size or Duration not valid");
            err.exec();
    }
    else{
        moviePtr->setDescription(descrInp->toPlainText());
        moviePtr->setPublicationDate(pubDateInp->date());
        moviePtr->setInsertionDate(insDateInp->date());
        moviePtr->setGenre(genreInp->text());
        moviePtr->setTitle(titleInp->text());
        moviePtr->setImagePath(imgPathInp->text());
        moviePtr->setDirector(directorInp->text());
        moviePtr->setSize(sizeInp->text().toDouble());
        moviePtr->setMediaPath(mediaPathInp->text());
        QVector<QString> newCast;
        for(int i = 0; i < actorsList->count();i++)
            newCast.push_back(actorsList->item(i)->text());
        moviePtr->setCast(newCast);
        moviePtr->setDuration(QTime(durInpH->text().toInt(),durInpM->text().toInt(),durInpS->text().toInt()));

        emit classEditor::accepted();

    }
}

void movieEditor::updateImage(){
    imgPathInp->setText(QFileDialog::getOpenFileName(this,"Find file","","Image Files (*.png *.jpg *.jpeg"));
    image->setPixmap(QPixmap(imgPathInp->text()).scaled(this->width()*0.2,this->width()*0.2,Qt::KeepAspectRatio));
}

void movieEditor::updateMedia(){
    mediaPathInp->setText(QFileDialog::getOpenFileName(this,"Find file","","(*.mp4)"));
}

void movieEditor::addActorCommand(){actorsList->addItem(actorInp->text());actorInp->clear();}

void movieEditor::deleteActorCommand(){actorsList->takeItem(actorsList->currentRow());}

item* movieEditor::getItem()const{
    return moviePtr;
}
