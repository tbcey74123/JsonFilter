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

#define maxWidth 800
#define maxHeight 600

Window::Window(QWidget *parent) : QWidget(parent) {

   setFixedSize(maxWidth, maxHeight);
   content = new ContentBox(this);
   content->setBasedBox(true);

   scroll = new QScrollArea(this);

   scroll->setFixedSize(800, height());
   scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   scroll->setWidget(content);

}

ContentBox *Window::getContentBox() { return content; }
QScrollArea *Window::getScroll() { return scroll; }



ContentBox::ContentBox(QWidget *parent) : QWidget(parent){
    index = 0;

    setFixedWidth(parent->width() - parent->style()->pixelMetric(QStyle::PM_ScrollBarExtent) - 2);

    //setFixedHeight(600);

    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);

    setAutoFillBackground(true);
    setPalette(pal);

    layout = new QVBoxLayout;

    //set the layout to the center.
    layout->setContentsMargins((width() - JsonUnitBox::DEFAULT_WIDTH) / 2, 10, (width() - JsonUnitBox::DEFAULT_WIDTH) / 2, 10);
    setLayout(layout);

    qDebug() << parent->size();
    qDebug() << parent->sizeHint();
    addButton();
}

bool ContentBox::isBasedBox() { return isBased; }
void ContentBox::setBasedBox(bool flag) { isBased = flag; }

void ContentBox::resizeBySizeHint() {


    setMinimumSize(sizeHint());

    if(parent() && !isBased) {
        ContentBox *p = dynamic_cast <ContentBox *>(parent());
        p->resizeBySizeHint();
    }
}

void ContentBox::addButton() {

    JsonUnitBox *newBox = new JsonUnitBox("button" + QString::number(index++), this);
    layout->addWidget(newBox);
}

/*
SubBox::SubBox(ContentBox *parent){

    setParent(parent);

    setMinimumSize(150, 200);
    setVisible(false);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::black);

    setAutoFillBackground(true);
    setPalette(pal);


}

bool SubBox::isButtonAdd() { return buttonAdd; }

void SubBox::display() {

    ContentBox *parentBox = dynamic_cast <ContentBox *>(parent());

    if(isVisible()) {
        setVisible(false);
        parentBox->resize(parentBox->width(), parentBox->height() - 200);
    }else {
        if(!buttonAdd) {
            addButton();
            buttonAdd = true;
        }
        setVisible(true);
        parentBox->resize(parentBox->width(), parentBox->height() + 200);
    }

}
*/
