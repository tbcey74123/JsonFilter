#include "jsonunitbox.h"
#include "window.h"

#define defaultWidth  JsonUnitBox::DEFAULT_WIDTH
#define defaultHeight JsonUnitBox::DEFAULT_HEIGHT

#include <QDebug>
#include <QWidget>
#include <QLinkedList>
#include <QPalette>


JsonUnitBox::JsonUnitBox(QWidget *parent) : JsonUnitBox("", parent) {}

JsonUnitBox::JsonUnitBox(const QString &text, QWidget *parent) : QPushButton(text, parent) {
    qDebug() << "test2";
    setFixedSize(defaultWidth, defaultHeight);
    if(parent) {

        layout = dynamic_cast <QVBoxLayout *>(parent->layout());
    }
    QObject::connect(this, &JsonUnitBox::pressed, [=]() {
        qDebug() << "test";
        if(!layout)
            return;
        JsonUnitBox *newBox = new JsonUnitBox("box");
        qDebug() << "test2";
        layout->insertWidget(layout->indexOf(this) + 1, newBox);
        newBox->setVisible(true);
        parent->setMinimumSize(parent->sizeHint());
    });
}

void JsonUnitBox::setLayout(QVBoxLayout *layout) {
    this->layout = layout;
}


void JsonUnitBox::setSubBox(SubBox *box) {
    subBox = box;
}

void JsonUnitBox::buttonPressed() {

    //dynamic_cast <ContentBox *>(parent())->insertButton(0);
    subBox->setVisible(!subBox->isVisible());
}

