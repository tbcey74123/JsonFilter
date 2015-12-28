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
    subBox = NULL;
    setFixedSize(defaultWidth, defaultHeight);
    if(parent) {

        layout = dynamic_cast <QVBoxLayout *>(parent->layout());
    }
    QObject::connect(this, &JsonUnitBox::pressed, [=]() {

        if(!layout)
            return;
        if(!subBox) {
            qDebug() << "testtt";
            subBox = new ContentBox(parent);
            layout->insertWidget(layout->indexOf(this) + 1, subBox);
            subBox->setVisible(true);
            dynamic_cast <ContentBox *>(parent)->resizeBySizeHint();
            //parent->setMinimumSize(parent->sizeHint());
        }else {
            subBox->setVisible(!subBox->isVisible());
            dynamic_cast <ContentBox *>(parent)->resizeBySizeHint();
        //JsonUnitBox *newBox = new JsonUnitBox("box");
        }
        qDebug() << "test2";
        qDebug() << parent->sizeHint();
    });
}

void JsonUnitBox::setLayout(QVBoxLayout *layout) {
    this->layout = layout;
}
