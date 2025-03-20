#include "jsonVisitor.h"
#include "book.h"
#include "movie.h"
#include "song.h"
#include "collection.h"
#include "generalitem.h"
#include <QJsonArray>
#include <QJsonValue>
#include <QVariant>


QJsonObject jsonVisitor::getObject(){return jObj;}

void jsonVisitor::visit(const item& item){
    jObj["insertionDate"] = item.getInsertionDate().toString(Qt::ISODate);
    jObj["description"] = item.getDescription();
    jObj["imagePath"] = item.getImagePath();
}

void jsonVisitor::visit(const media& media){
    jsonVisitor::visit(static_cast<const item&>(media)); //safe upcast to make a static call to visit(const item)&
    jObj["publicationDate"] = media.getPublicationDate().toString(Qt::ISODate);
    jObj["genre"] = media.getGenre();
    jObj["title"] = media.getTitle();
}

void jsonVisitor::visit(const digital& digital){
    jsonVisitor::visit(static_cast<const item&>(digital));
    jObj["size"] = digital.getSize();
    jObj["mediaPath"] = digital.getMediaPath();
}

void jsonVisitor::visit(const book& book){
    jsonVisitor::visit(static_cast<const media&>(book));
    jObj["classType"] = QJsonValue::fromVariant("book");
    jObj["author"] = book.getAuthor();
    jObj["pages"] = QString::number(book.getPages());
}

void jsonVisitor::visit(const movie& movie){
    jsonVisitor::visit(static_cast<const media&>(movie));
    jsonVisitor::visit(static_cast<const digital&>(movie));
    jObj["classType"] = QJsonValue::fromVariant("movie");
    QJsonArray jCast;
    for(const QString& actor : movie.getCast())
        jCast.append(actor);
    jObj["cast"] = jCast;
    jObj["director"] = movie.getDirector();
    jObj["duration"] = movie.getDuration().toString();
}

void jsonVisitor::visit(const song& song){
    jsonVisitor::visit(static_cast<const media&>(song));
    jsonVisitor::visit(static_cast<const digital&>(song));
    jObj["classType"] = QJsonValue::fromVariant("song");
    jObj["artist"] = song.getArtist();
    jObj["duration"] = song.getDuration().toString();
}

void jsonVisitor::visit(const generalItem& gItem){
    jsonVisitor::visit(static_cast<const item&>(gItem));
    jObj["classType"] = QJsonValue::fromVariant("generalItem");
    jObj["name"] = gItem.getName();

}

void jsonVisitor::visit(const collection& coll){
    QJsonArray jArray;
    for(const item* it : coll.getItems()){
        jsonVisitor jVisitor;
        it->accept(jVisitor);
        jArray.append(jVisitor.getObject());
    }
    jObj["items"] = jArray;
}
