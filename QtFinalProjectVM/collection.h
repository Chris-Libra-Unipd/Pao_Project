#ifndef COLLECTION_H
#define COLLECTION_H

#include "item.h"
#include <QVector>
#include "jsonVisitor.h"

class collection{
private:
    QVector<item*> items;
public:
    ~collection();
    collection& operator=(const collection&  other);
    collection(const collection&);
    collection() = default;

    static void copy(QVector<item*>& target, const QVector<item*>& toCopy);
    static void destroy(QVector<item*>& vec);

    void addItem(item* item);
    void removeItem(item* item);
    void clearAll();

    const QVector<item*>& getItems() const;

    void accept(jsonVisitor& jVisitor) const;

    QVector<item*> applyFilter(const filter& filter) const;
    QVector<item*> makeSearch(const QString& keyword) const;

    bool saveCollectionAs() const;
    bool loadCollection();
};

#endif // COLLECTION_H
