#include "collection.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QFileDialog>
#include <QJsonDocument>
#include "jsonVisitor.h"
#include "jsonreader.h"

void collection::copy(QVector<item*>& target, const QVector<item*>& toCopy){
    for(item* it : toCopy)
        target.push_back(it->clone());
}

void collection::destroy(QVector<item*>& vec){
    for(item* it : vec) delete it;
}

collection::~collection(){destroy(items);}

collection& collection::operator=(const collection& other){
    if(&other!=this){
        clearAll();
        copy(items, other.items);
    }
    return *this;
}

collection::collection(const collection& other){
    copy(items, other.items);
}

void collection::addItem(item* item){items.push_back(item);}

void collection::removeItem(item* item){
    items.removeOne(item);
    delete item;
}

void collection::clearAll(){
    destroy(items);
    items.clear();
}

const QVector<item*>& collection::getItems() const{return items;}

void collection::accept(jsonVisitor& jVisitor)const{jVisitor.visit(*this);}

QVector<item*> collection::applyFilter(const filter& filter) const{
    QVector<item*> result;
    for(item* it : items)
        if(it->isRelevant(filter))
            result.push_back(it);
    return result;
}

QVector<item*> collection::makeSearch(const QString& keyword) const{
    QVector<float> relevance;
    QVector<int> indexes;
    for(int i = 0; i < items.size(); i++){
        float relevValue = items[i]->howRelevant(keyword);
        if(relevValue > 0.7){     //items with low relevance are excluded from the result list
            relevance.push_back(relevValue);
            indexes.push_back(i);
        }
    }
    //an unordered vector of relevant item pointers has been created along with a vector of their indexes
    //orders the vector relevance in descending order and moves the same elements in the indexes vector
    HeapSort::sort(relevance,indexes);

    QVector<item*> result;
    for(const int i : indexes)
        result.push_back(items[i]);
    return result;
}

bool collection::saveCollectionAs() const{
    QString filePath = QFileDialog::getSaveFileName(nullptr,"Save as","","JSON (*.json)");
    QFile collFile(filePath);
    if(!collFile.open(QIODevice::WriteOnly)){
        qWarning("Couldn't open file\n");
        return 0;
    }

    jsonVisitor jVisitor;
    accept(jVisitor);
    QJsonDocument jDoc(jVisitor.getObject());
    collFile.write(jDoc.toJson());
    collFile.close();
    return 1;
}

bool collection::loadCollection(){
    QString filePath = QFileDialog::getOpenFileName(nullptr,"Open file","","JSON (*.json)");
    QFile collFile(filePath);
    if(!collFile.open(QIODevice::ReadOnly)){
        qWarning("Couldnt open file\n");
        return 0;
    }
    QJsonDocument jDoc(QJsonDocument::fromJson(collFile.readAll()));

    jsonReader reader;
    reader.readCollection(*this,jDoc.object());
    collFile.close();
    return 1;
}



