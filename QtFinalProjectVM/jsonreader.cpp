#include "jsonreader.h"
#include <QJsonValue>
#include <QJsonArray>
#include <QString>
#include "book.h"
#include "movie.h"
#include "song.h"
#include "generalitem.h"
#include "collection.h"


item* jsonReader::read(const QJsonObject& jObj){
    item* newObj;
    QJsonValue type = jObj["classType"];
    if(type.toString().compare("book") == 0){
        newObj = new book(QDate::fromString(jObj["insertionDate"].toString(),Qt::ISODate),
                          jObj["description"].toString(),
                          jObj["imagePath"].toString(),
                          QDate::fromString(jObj["publicationDate"].toString(),Qt::ISODate),
                          jObj["genre"].toString(),
                          jObj["title"].toString(),
                          jObj["author"].toString(),
                          jObj["pages"].toString().toUInt());
    }
    if(type.toString().compare("movie") == 0){
        QVector<QString> loadedCast;
        QJsonArray arr = jObj["cast"].toArray();
        for(const QJsonValue& actor : arr)
            loadedCast.append(actor.toString());

        newObj = new movie(QDate::fromString(jObj["insertionDate"].toString(),Qt::ISODate),
                           jObj["description"].toString(),
                           jObj["imagePath"].toString(),
                           QDate::fromString(jObj["publicationDate"].toString(),Qt::ISODate),
                           jObj["genre"].toString(),
                           jObj["title"].toString(),
                           jObj["size"].toDouble(),
                           jObj["mediaPath"].toString(),
                           loadedCast,
                           jObj["director"].toString(),
                           QTime::fromString(jObj["duration"].toString()));
    }
    if(type.toString().compare("song") == 0){
        newObj = new song(QDate::fromString(jObj["insertionDate"].toString(),Qt::ISODate),
                jObj["description"].toString(),
                jObj["imagePath"].toString(),
                QDate::fromString(jObj["publicationDate"].toString(),Qt::ISODate),
                jObj["genre"].toString(),
                jObj["title"].toString(),
                jObj["size"].toDouble(),
                jObj["mediaPath"].toString(),
                jObj["artist"].toString(),
                QTime::fromString(jObj["duration"].toString()));
    }
    if(type.toString().compare("generalItem") == 0){
        newObj = new generalItem(QDate::fromString(jObj["insertionDate"].toString(),Qt::ISODate),
                                 jObj["description"].toString(),
                                 jObj["imagePath"].toString(),
                                 jObj["name"].toString());
    }
    return newObj;
}

void jsonReader::readCollection(collection& coll,const QJsonObject& jObj){
    QJsonArray itArr = jObj["items"].toArray();
    for(const QJsonValue& jv : itArr){
        coll.addItem(read(jv.toObject()));
    }
}
