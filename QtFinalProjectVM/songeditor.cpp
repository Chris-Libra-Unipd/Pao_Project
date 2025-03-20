#include "songeditor.h"

songEditor::songEditor(song* songPar, bool flag, QWidget* parent):classEditor(parent),
    songPtr(songPar),
    Glayout(new QGridLayout()),
    layout(new QVBoxLayout(this)),
    descr(new QLabel("Description: ",this)),
    insDate(new QLabel("Insertion Date: ",this)),
    imgPath(new QLabel("Image Path*: ",this)),
    genre(new QLabel("Genre: ",this)),
    title(new QLabel("Title*: ",this)),
    pubDate(new QLabel("Publication Date: ",this)),
    mediaPath(new QLabel("Audio Path",this)),
    size(new QLabel("Size",this)),
    artist(new QLabel("Artist*",this)),
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
    artistInp(new QLineEdit(this)),
    durInpH(new QLineEdit(this)),
    durInpM(new QLineEdit(this)),
    durInpS(new QLineEdit(this)),
    findPath(new QPushButton("Find path",this)),
    findPathMedia(new QPushButton("Find path",this)),
    edit(flag)

{
    //body
    //constructor body
    header=new QLabel("Song creation",this);
    confirm=new QPushButton("Confirm",this);
    cancel=new QPushButton("Cancel",this);
    header->setAlignment(Qt::AlignCenter);

    insDateInp->setDisplayFormat("dd.MM.yyyy");
    pubDateInp->setDisplayFormat("dd.MM.yyyy");

    imgPathInp->setText(":/media/noImg.jpg");

    durInpH->setPlaceholderText("h");
    durInpM->setPlaceholderText("min");
    durInpS->setPlaceholderText("sec");

    //if edit flag = 1 fill the input lines with the book's fields
    if(edit){
        header->setText("Song editing");
        descrInp->setText(songPtr->getDescription());
        pubDateInp->setDate(songPtr->getPublicationDate());
        insDateInp->setDate(songPtr->getInsertionDate());
        genreInp->setText(songPtr->getGenre());
        titleInp->setText(songPtr->getTitle());
        imgPathInp->setText(songPtr->getImagePath());
        mediaPathInp->setText(songPtr->getMediaPath());
        if(!(imgPathInp->text().isEmpty()))
            image->setPixmap(QPixmap(songPtr->getImagePath()).scaled(this->width()*0.2,this->width()*0.2,Qt::KeepAspectRatio));
        sizeInp->setText(QString::number(songPtr->getSize()));
        artistInp->setText(songPtr->getArtist());
        durInpH->setText(QString::number(songPtr->getDuration().hour()));
        durInpM->setText(QString::number(songPtr->getDuration().minute()));
        durInpS->setText(QString::number(songPtr->getDuration().second()));

    }
    QHBoxLayout* intHLayout = new QHBoxLayout();
    intHLayout->addWidget(durInpH);
    intHLayout->addWidget(durInpM);
    intHLayout->addWidget(durInpS);

    //populate the layout
    Glayout->addWidget(title,0,0,Qt::AlignRight);
    Glayout->addWidget(titleInp,0,1);
    Glayout->addWidget(artist,1,0,Qt::AlignRight);
    Glayout->addWidget(artistInp,1,1);
    Glayout->addWidget(pubDate,2,0,Qt::AlignRight);
    Glayout->addWidget(pubDateInp,2,1);
    Glayout->addWidget(genre,3,0,Qt::AlignRight);
    Glayout->addWidget(genreInp,3,1);
    Glayout->addWidget(duration,4,0,Qt::AlignRight);
    Glayout->addLayout(intHLayout,4,1);
    Glayout->addWidget(insDate,5,0,Qt::AlignRight);
    Glayout->addWidget(insDateInp,5,1);
    Glayout->addWidget(imgPath,6,0,Qt::AlignRight);
    Glayout->addWidget(imgPathInp,6,1);
    Glayout->addWidget(findPath,6,2);
    Glayout->addWidget(mediaPath,7,0,Qt::AlignRight);
    Glayout->addWidget(mediaPathInp,7,1);
    Glayout->addWidget(findPathMedia,7,2);
    Glayout->addWidget(descr,8,0,Qt::AlignRight | Qt::AlignTop);
    Glayout->addWidget(descrInp,8,1);
    Glayout->addWidget(size,9,0,Qt::AlignRight);
    Glayout->addWidget(sizeInp,9,1);

    Glayout->addWidget(image,0,3);
    Glayout->addWidget(confirm,9,3,Qt::AlignBottom);
    Glayout->addWidget(cancel,9,2,Qt::AlignBottom);

    layout->addWidget(header);
    layout->addLayout(Glayout);

    QObject::connect(findPath, &QPushButton::clicked,this, &songEditor::updateImage);
    QObject::connect(findPathMedia, &QPushButton::clicked,this,&songEditor::updateMedia);

    QObject::connect(confirm, &QPushButton::clicked,this, &songEditor::updateFields);
    QObject::connect(cancel, &QPushButton::clicked,this, &classEditor::rejected);
}

void songEditor::updateFields(){
    bool okH,okM,okS;
    durInpH->text().toInt(&okH);
    durInpM->text().toInt(&okM);
    durInpS->text().toInt(&okS);
    if(titleInp->text().isEmpty() || artistInp->text().isEmpty() || imgPathInp->text().isEmpty()){
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
        songPtr->setDescription(descrInp->toPlainText());
        songPtr->setPublicationDate(pubDateInp->date());
        songPtr->setInsertionDate(insDateInp->date());
        songPtr->setGenre(genreInp->text());
        songPtr->setTitle(titleInp->text());
        songPtr->setImagePath(imgPathInp->text());
        songPtr->setArtist(artistInp->text());
        songPtr->setSize(sizeInp->text().toDouble());
        songPtr->setMediaPath(mediaPathInp->text());
        songPtr->setDuration(QTime(durInpH->text().toInt(),durInpM->text().toInt(),durInpS->text().toInt()));
        emit classEditor::accepted();
    }
}

void songEditor::updateImage(){
    imgPathInp->setText(QFileDialog::getOpenFileName(this,"Find file","","Image Files (*.png *.jpg *.jpeg"));
    image->setPixmap(QPixmap(imgPathInp->text()).scaled(this->width()*0.2,this->width()*0.2,Qt::KeepAspectRatio));
}

void songEditor::updateMedia(){
    mediaPathInp->setText(QFileDialog::getOpenFileName(this,"Find file","","(*.mp3)"));
}

item* songEditor::getItem()const{
    return songPtr;
}
