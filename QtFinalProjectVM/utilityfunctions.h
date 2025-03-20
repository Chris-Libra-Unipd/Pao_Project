#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H

#include <QString>
#include <math.h>

QString longestCommonSubString(const QString& src,const QString& keyword);

float evaluateLCSS(const QString& src,const QString& keyword);

namespace HeapSort{
    template<class T>
    void swap(T& v1, T& v2);
    void minHeapify(QVector<float>& releVec, QVector<int>& indexVec, int pos, int dim);
    void buildMinHeap(QVector<float>& releVec, QVector<int>& indexVec);
    void sort(QVector<float>& releVec, QVector<int>& indexVec);
}
#endif // UTILITYFUNCTIONS_H
