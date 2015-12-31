#include "window.h"
#include "jsonunitbox.h"

#include <QDebug>
#include <QWidget>
#include <QPalette>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QTextBrowser>
#include <QStyle>
#include <QJsonDocument>
#include <QJSonObject>
#include <QJsonArray>

#define maxWidth 800
#define maxHeight 600

Window::Window(QWidget *parent) : QWidget(parent) {

   setFixedSize(maxWidth, maxHeight);
   content = new ContentBox(this);
   content->setBasedBox(true);

   scroll = new QScrollArea(this);

   scroll->setFixedSize(800, height());
   //scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   scroll->setWidget(content);

}

ContentBox *Window::getContentBox() { return content; }
QScrollArea *Window::getScroll() { return scroll; }



ContentBox::ContentBox(QWidget *parent) : QWidget(parent){
    index = 0;

    //setFixedWidth(parent->width() - parent->style()->pixelMetric(QStyle::PM_ScrollBarExtent) - 2);
    setFixedWidth(600);


    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);

    setAutoFillBackground(true);
    setPalette(pal);


    layout = new QVBoxLayout;

    //set the layout to the center.
    layout->setContentsMargins((width() - JsonUnitBox::DEFAULT_WIDTH) / 2, 10, (width() - JsonUnitBox::DEFAULT_WIDTH) / 2, 10);
    setLayout(layout);

    addButton();
    defaultSize = sizeHint();
}

bool ContentBox::isBasedBox() { return isBased; }
void ContentBox::setBasedBox(bool flag) { isBased = flag; }

void ContentBox::resizeBySizeHint(bool isDefault) {

    if(isDefault) {
        setFixedSize(defaultSize);
        setMinimumSize(defaultSize);
    }
    else
        setMinimumSize(sizeHint());


    if(parent() && !isBased) {
        ContentBox *p = dynamic_cast <ContentBox *>(parent());
        p->resizeBySizeHint(isDefault);
    }
}

void ContentBox::handleJson(const QJsonDocument &document) {

    if(document.isEmpty()) return;
    if(document.isObject()) {
       QJsonObject obj = document.object();
       for(QJsonObject::Iterator i = obj.begin(); i != obj.end(); ++i) {
           addButton(i.key());
       }
    }else if(document.isArray()) {

    }
}

//public slots
void ContentBox::addButton() {
    addButton(" ");
}
void ContentBox::addButton(const QString &text) {
    JsonUnitBox *newBox = new JsonUnitBox(text, this);
    layout->addWidget(newBox);
}

