#include <QApplication>
#include "collection.h"
#include "generalitem.h"
#include "song.h"
#include "movie.h"
#include "book.h"
#include <QDate>
#include "filter.h"
#include <QDebug>
#include "utilityfunctions.h"
#include "mediaplayervisitor.h"
#include "playerbuttonsWidget.h"
#include "addeditvisitor.h"
#include "movie.h"
#include "detailvisitor.h"
#include "previewvisitor.h"
#include <QVector>
#include "toolbarWidget.h"
#include "filterwidget.h"
#include "sidebar.h"
#include "showlistWidget.h"
#include "bodyWidget.h"
#include "fullwindowWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    fullWindow collWindow;
    collWindow.show();

    return a.exec();
}


