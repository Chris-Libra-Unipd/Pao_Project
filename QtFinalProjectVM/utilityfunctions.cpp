#include "utilityfunctions.h"
#include <QDebug>

QString longestCommonSubString(const QString& src,const QString& keyword){
    QString res;
    QString temp;
    int j = 0;
    for(int i = 0; i < src.length(); i++){
        j = 0;
        while(j < src.length() - i && j < keyword.length() && (src[i+j] == keyword[j].toUpper() || src[i+j] == keyword[j].toLower()) ){
            temp.push_back(src[i+j]);
            j++;
        }
        if(temp.length()>res.length())
            res = temp;
        temp.clear();
    }
    return res;
}

float evaluateLCSS(const QString& src,const QString& keyword){
    QString res = longestCommonSubString(src,keyword);
    return float(res.length())/float(keyword.length());
}
template<class T>
void HeapSort::swap(T& v1, T& v2){
    T temp = v1;
    v1 = v2;
    v2 = temp;
}

//HEAPSORT

void HeapSort::minHeapify(QVector<float>& releVec, QVector<int>& indexVec, int pos, int dim){
    int left = 2*pos+1;
    int right = 2*pos+2;
    int max = pos;
    if(left < dim && releVec[left] < releVec[max]) max = left;
    if(right < dim && releVec[right] < releVec[max]) max = right;
    if(max != pos){
        swap(releVec[pos],releVec[max]);
        swap(indexVec[pos],indexVec[max]);
        minHeapify(releVec,indexVec,max,dim);
    }
}

void HeapSort::buildMinHeap(QVector<float>& releVec, QVector<int>& indexVec){
    int dim = releVec.size();
    for(int i = dim/2 - 1; i >= 0 ; i--)
        minHeapify(releVec, indexVec, i,dim);
}

void HeapSort::sort(QVector<float>& releVec, QVector<int>& indexVec){
    buildMinHeap(releVec,indexVec);
    int dim = releVec.size();
    for(int i = dim-1; i > 0 ; i--){
        swap(releVec[0],releVec[i]);
        swap(indexVec[0],indexVec[i]);
        minHeapify(releVec, indexVec, 0, i);
    }
}

