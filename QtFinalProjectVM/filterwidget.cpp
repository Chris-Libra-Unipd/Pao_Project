#include "filterwidget.h"
#include "book.h"
#include "movie.h"
#include "song.h"
#include "generalitem.h"

filterWidget::filterWidget(QWidget* parent) :  QWidget(parent),
//header(new QPushButton(QIcon(":/icons/filter.png"),"Filters", this)),
showHideButton(new QPushButton(QIcon(":/icons/down-arrow.png"),"  Filters",this)),
insertionDate(new QLabel("Insertion date",this)),
publicationDate(new QLabel("Publication date",this)),
duration(new QLabel("Duration",this)),
genre(new QLabel("Genre",this)),
actor(new QLabel("Actor",this)),
author(new QLabel("Author",this)),
artist(new QLabel("Artist",this)),
pages(new QLabel("Pages",this)),
size(new QLabel("Size",this)),
type(new QLabel("Type",this)),

layout(new QGridLayout(this)),
confirm(new QPushButton("Confirm",this)),
resetButton(new QPushButton("Reset",this)),
cancel(new QPushButton("Cancel",this)),

min(new QLabel("Min",this)),
max(new QLabel("Max",this)),
insertionDateMinInp(new QLineEdit(this)),
insertionDateMaxInp(new QLineEdit(this)),
publicationDateMinInp(new QLineEdit(this)),
publicationDateMaxInp(new QLineEdit(this)),
durationMinHInp(new QLineEdit(this)),
durationMinMInp(new QLineEdit(this)),
durationMinSInp(new QLineEdit(this)),
durationMaxHInp(new QLineEdit(this)),
durationMaxMInp(new QLineEdit(this)),
durationMaxSInp(new QLineEdit(this)),
genreInp(new QLineEdit(this)),
actorInp(new QLineEdit(this)),
authorInp(new QLineEdit(this)),
artistInp(new QLineEdit(this)),
pagesMinInp(new QLineEdit(this)),
pagesMaxInp(new QLineEdit(this)),
sizeMinInp(new QLineEdit(this)),
sizeMaxInp(new QLineEdit(this)),
typeInp(new QComboBox(this)),
isHidden(0)
{
    layout->setContentsMargins(0,0,0,0);

    durationMinHInp->setPlaceholderText("h");
    durationMinMInp->setPlaceholderText("min");
    durationMinSInp->setPlaceholderText("sec");
    durationMaxHInp->setPlaceholderText("h");
    durationMaxMInp->setPlaceholderText("min");
    durationMaxSInp->setPlaceholderText("sec");

    insertionDateMinInp->setPlaceholderText("yyyy-mm-dd");
    insertionDateMaxInp->setPlaceholderText("yyyy-mm-dd");
    publicationDateMinInp->setPlaceholderText("yyyy-mm-dd");
    publicationDateMaxInp->setPlaceholderText("yyyy-mm-dd");

    typeInp->addItem("");
    typeInp->addItem(QIcon(":/icons/book.png"),"Book");
    typeInp->addItem(QIcon(":/icons/video.png"),"Movie");
    typeInp->addItem(QIcon(":/icons/music.png"),"Song");
    typeInp->addItem(QIcon(":/icons/box.png"),"General Item");

    layout->addWidget(showHideButton,0,0);

    layout->addWidget(min,1,1,Qt::AlignCenter);
    layout->addWidget(max,1,2,Qt::AlignCenter);

    layout->addWidget(insertionDate,2,0,Qt::AlignRight);
    layout->addWidget(insertionDateMinInp,2,1);
    layout->addWidget(insertionDateMaxInp,2,2);

    layout->addWidget(publicationDate,3,0,Qt::AlignRight);
    layout->addWidget(publicationDateMinInp,3,1);
    layout->addWidget(publicationDateMaxInp,3,2);

    layout->addWidget(duration,4,0,Qt::AlignRight);
    QHBoxLayout* minLayout = new QHBoxLayout();
    QHBoxLayout *maxLayout = new QHBoxLayout();
    minLayout->addWidget(durationMinHInp);
    minLayout->addWidget(durationMinMInp);
    minLayout->addWidget(durationMinSInp);
    maxLayout->addWidget(durationMaxHInp);
    maxLayout->addWidget(durationMaxMInp);
    maxLayout->addWidget(durationMaxSInp);
    layout->addLayout(minLayout,4,1);
    layout->addLayout(maxLayout,4,2);

    layout->addWidget(pages,5,0,Qt::AlignRight);
    layout->addWidget(pagesMinInp,5,1);
    layout->addWidget(pagesMaxInp,5,2);

    layout->addWidget(size,6,0,Qt::AlignRight);
    layout->addWidget(sizeMinInp,6,1);
    layout->addWidget(sizeMaxInp,6,2);

    layout->addWidget(genre,7,0,Qt::AlignRight);
    layout->addWidget(genreInp,7,1);

    layout->addWidget(author,8,0,Qt::AlignRight);
    layout->addWidget(authorInp,8,1);

    layout->addWidget(actor,9,0,Qt::AlignRight);
    layout->addWidget(actorInp,9,1);

    layout->addWidget(artist,10,0,Qt::AlignRight);
    layout->addWidget(artistInp,10,1);

    layout->addWidget(type,11,0,Qt::AlignRight);
    layout->addWidget(typeInp,11,1);

    layout->addWidget(cancel,12,0);
    layout->addWidget(resetButton,12,1);
    layout->addWidget(confirm,12,2);

    change();

    connect(showHideButton, &QPushButton::clicked, this, &filterWidget::change);
    connect(resetButton, &QPushButton::clicked, this, &filterWidget::reset);
    connect(cancel, &QPushButton::clicked, this, [this]{reset();change();});

    connect(confirm, &QPushButton::clicked, this,[this]{
        filter* newFilterPtr = buildFilter();
        if(newFilterPtr)
            emit filterCreated(newFilterPtr);
        else{
            QMessageBox err;
            err.setWindowTitle("Error");
            err.setText("Some values are not compatible");
            err.exec();
        }
    });

}

void filterWidget::change(){
    bool x = 1;
    if(isHidden){
        isHidden = 0;
        showHideButton->setIcon(QIcon(":/icons/up-arrow.png"));
    }else{
        isHidden = 1;
        showHideButton->setIcon(QIcon(":/icons/down-arrow.png"));
        x = 0;
    }

    min->setVisible(x);
    max->setVisible(x);
    insertionDate->setVisible(x);
    publicationDate->setVisible(x);
    duration->setVisible(x);
    genre->setVisible(x);
    actor->setVisible(x);
    author->setVisible(x);
    artist->setVisible(x);
    pages->setVisible(x);
    size->setVisible(x);
    type->setVisible(x);

    confirm->setVisible(x);
    resetButton->setVisible(x);
    cancel->setVisible(x);

    insertionDateMinInp->setVisible(x);
    insertionDateMaxInp->setVisible(x);
    publicationDateMinInp->setVisible(x);
    publicationDateMaxInp->setVisible(x);
    durationMinHInp->setVisible(x);
    durationMinMInp->setVisible(x);
    durationMinSInp->setVisible(x);
    durationMaxHInp->setVisible(x);
    durationMaxMInp->setVisible(x);
    durationMaxSInp->setVisible(x);
    genreInp->setVisible(x);
    actorInp->setVisible(x);
    authorInp->setVisible(x);
    artistInp->setVisible(x);
    pagesMinInp->setVisible(x);
    pagesMaxInp->setVisible(x);
    sizeMinInp->setVisible(x);
    sizeMaxInp->setVisible(x);
    typeInp->setVisible(x);

    emit appearenceChanged();
}


void filterWidget::reset(){
    insertionDateMinInp->clear();
    insertionDateMaxInp->clear();
    publicationDateMinInp->clear();
    publicationDateMaxInp->clear();
    durationMinHInp->clear();
    durationMinMInp->clear();
    durationMinSInp->clear();
    durationMaxHInp->clear();
    durationMaxMInp->clear();
    durationMaxSInp->clear();
    genreInp->clear();
    actorInp->clear();
    authorInp->clear();
    artistInp->clear();
    pagesMinInp->clear();
    pagesMaxInp->clear();
    sizeMinInp->clear();
    sizeMaxInp->clear();
    typeInp->setCurrentIndex(0);
}



filter* filterWidget::buildFilter(){
    filter* f = new filter();
    //coherence check for each field
    //if the field is not empty and has the correct format it's added to the filter
    if(!insertionDateMinInp->text().isEmpty()){
        QDate temp =  QDate::fromString(insertionDateMinInp->text(),Qt::ISODate);
        if(temp.isValid())
            f->setInsertionDateMin(temp);
        else
            return nullptr;
    }
    if(!insertionDateMaxInp->text().isEmpty()){
        QDate temp =  QDate::fromString(insertionDateMaxInp->text(),Qt::ISODate);
        if(temp.isValid())
            f->setInsertionDateMax(temp);
        else
            return nullptr;
    }
    if(!publicationDateMinInp->text().isEmpty()){
        QDate temp =  QDate::fromString(publicationDateMinInp->text(),Qt::ISODate);
        if(temp.isValid())
            f->setPublicationDateMin(temp);
        else
            return nullptr;
    }
    if(!publicationDateMaxInp->text().isEmpty()){
        QDate temp =  QDate::fromString(publicationDateMaxInp->text(),Qt::ISODate);
        if(temp.isValid())
            f->setPublicationDateMax(temp);
        else
            return nullptr;
    }
    if(!sizeMinInp->text().isEmpty()){
        bool ok;
        sizeMinInp->text().toDouble(&ok);
        if(ok)
            f->setSizeMin(sizeMinInp->text().toDouble());
        else
            return nullptr;
    }
    if(!sizeMaxInp->text().isEmpty()){
        bool ok;
        sizeMaxInp->text().toDouble(&ok);
        if(ok)
            f->setSizeMax(sizeMaxInp->text().toDouble());
        else
            return nullptr;
    }
    if(!pagesMinInp->text().isEmpty()){
        bool ok;
        pagesMinInp->text().toUInt(&ok);
        if(ok)
            f->setPagesMin(pagesMinInp->text().toUInt());
        else
            return nullptr;
    }
    if(!pagesMaxInp->text().isEmpty()){
        bool ok;
        pagesMaxInp->text().toUInt(&ok);
        if(ok)
            f->setPagesMax(pagesMaxInp->text().toUInt());
        else
            return nullptr;
    }
    if(!durationMinHInp->text().isEmpty() || !durationMinMInp->text().isEmpty() || !durationMinSInp->text().isEmpty()){
        bool okH,okM,okS;
        durationMinHInp->text().toUInt(&okH);
        durationMinMInp->text().toUInt(&okM);
        durationMinSInp->text().toUInt(&okS);
        if(okH && okM && okS)
            f->setDurationMin(QTime(durationMinHInp->text().toUInt(),durationMinMInp->text().toUInt(),durationMinSInp->text().toUInt()));
        else
            return nullptr;
    }
    if(!durationMaxHInp->text().isEmpty() || !durationMaxMInp->text().isEmpty() || !durationMaxSInp->text().isEmpty()){
        bool okH,okM,okS;
        durationMaxHInp->text().toUInt(&okH);
        durationMaxMInp->text().toUInt(&okM);
        durationMaxSInp->text().toUInt(&okS);
        if(okH && okM && okS)
            f->setDurationMax(QTime(durationMaxHInp->text().toUInt(),durationMaxMInp->text().toUInt(),durationMaxSInp->text().toUInt()));
        else
            return nullptr;
    }
    if(!genreInp->text().isEmpty())
        f->setGenre(genreInp->text());
    if(!actorInp->text().isEmpty()){
        f->setActor(actorInp->text());
    }
    if(!authorInp->text().isEmpty())
        f->setAuthor(authorInp->text());
    if(!artistInp->text().isEmpty())
        f->setArtist(artistInp->text());

    if(!typeInp->currentText().isEmpty()){
        item* ptr = nullptr;
        if(typeInp->currentText() == "Book")
            ptr = new book();
        if(typeInp->currentText() == "Movie")
            ptr = new movie();
        if(typeInp->currentText() == "Song")
            ptr = new song();
        if(typeInp->currentText() == "General Item")
            ptr = new generalItem();
        f->setType(ptr);
    }
    return f;
}
