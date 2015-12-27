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
   QScrollArea *scroll = new QScrollArea(this);
   QVBoxLayout *vBox = new QVBoxLayout(scroll);
   ContentBox *contentBox = new ContentBox(scroll, this);
   QPushButton *button = new QPushButton("press", this);

   scroll->move(0, 100);
   scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   scroll->setWidget(contentBox);
   scroll->resize(maxWidth, maxHeight - 100);

   QObject::connect(button, SIGNAL(clicked(bool)), contentBox, SLOT(addButton()));
}


ContentBox::ContentBox(){
    index = 0;

    vBox = new QVBoxLayout;

    setLayout(vBox);
}

ContentBox::ContentBox(QScrollArea *scroll, QWidget *parent) : QWidget(parent) {

    index = 0;
    this->scroll = scroll;

    //substract the width of the bar
    setMinimumSize(parent->width() - parent->style()->pixelMetric(QStyle::PM_ScrollBarExtent), parent->height());

    vBox = new QVBoxLayout;

    buttonList = new QLinkedList<JsonUnitBox *>;

    for(int i = 0; i < index; i++) {
        JsonUnitBox *newBox = new JsonUnitBox("button" + QString::number(i), this);

        buttonList->append(newBox);
        vBox->addWidget(newBox);

        QObject::connect(newBox, SIGNAL(clicked(bool)), newBox, SLOT(buttonPressed()));
    }

    setLayout(vBox);

}

void ContentBox::insertButton(int insertIndex) {
    JsonUnitBox *newBox = new JsonUnitBox("button" + QString::number(index++), this);

    vBox->insertWidget(insertIndex, newBox);

    resize(width(), height() + 50);

    //QObject::connect(newBox, SIGNAL(pressed()), newBox, SLOT(buttonPressed()));
}

void ContentBox::addButton() {

    JsonUnitBox *newBox = new JsonUnitBox("button" + QString::number(index++), this);
    SubBox *subBox;

    qDebug() << "test";

    subBox = new SubBox(this);
    newBox->setSubBox(subBox);

    vBox->addWidget(newBox);
    vBox->addWidget(subBox);

    QObject::connect(newBox, SIGNAL(clicked(bool)), subBox, SLOT(display()));

    resize(width(), height() + 50);
}


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

