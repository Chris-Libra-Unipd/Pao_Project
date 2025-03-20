#ifndef JSONREADER_H
#define JSONREADER_H

#include <QJsonObject>

class item;
class collection;

class jsonReader {
public:
    void readCollection(collection& coll,const QJsonObject& jObj);
    item* read(const QJsonObject& jObj);
};

#endif // JSONREADER_H
