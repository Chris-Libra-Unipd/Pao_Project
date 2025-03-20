#include "sidebar.h"

sideBar::sideBar(QWidget* parent) : QWidget(parent),
searchBar(new QLineEdit(this)),
searchButton(new QPushButton(QIcon(":/icons/search.png"),"",this)),
filterSection(new filterWidget(this)),
showAll(new QPushButton(QIcon(":/icons/home.png"),"Show all",this)),
outerLayout(new QVBoxLayout(this)),
innerLayout(new QHBoxLayout())
{
    searchBar->setPlaceholderText("Search");
    innerLayout->addWidget(searchBar);
    innerLayout->addWidget(searchButton);
    innerLayout->addStretch();
    outerLayout->addLayout(innerLayout);
    outerLayout->addWidget(filterSection);
    outerLayout->addWidget(showAll);
    outerLayout->addStretch();

    outerLayout->setSpacing(10);

    connect(filterSection, &filterWidget::appearenceChanged,this, [this]{filterSection->updateGeometry();emit dimChanged();});
    connect(filterSection, &filterWidget::filterCreated,this, &sideBar::filterRequest);

    connect(searchBar,&QLineEdit::returnPressed,this, [this]{emit searchRequest(searchBar->text());});
    connect(searchButton,&QPushButton::clicked,this, [this]{emit searchRequest(searchBar->text());});

    connect(showAll,&QPushButton::clicked,this, &sideBar::showAllRequest);

    setMaximumWidth(2.5*sizeHint().width());

}

//for the stylesheet
void sideBar::paintEvent(QPaintEvent * event){
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
