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
            subBox = new ContentBox(parent);
            layout->insertWidget(layout->indexOf(this) + 1, subBox);
            subBox->setVisible(true);
            dynamic_cast <ContentBox *>(parent)->resizeBySizeHint(false);
            //parent->setMinimumSize(parent->sizeHint());
        }else {
            if(subBox->isVisible()) {
                //subBox->setVisible(false);
                //dynamic_cast <ContentBox *>(parent)->resizeBySizeHint(true);
                layout->removeWidget(subBox);
                subBox->setVisible(false);
                layout->setSizeConstraint(QLayout::SetFixedSize);

            }else {
                layout->addWidget(subBox);
                subBox->setVisible(true);

                //dynamic_cast <ContentBox *>(parent)->resizeBySizeHint(false);
            }

        //JsonUnitBox *newBox = new JsonUnitBox("box");
        }
    });
}

void JsonUnitBox::setLayout(QVBoxLayout *layout) {
    this->layout = layout;
}
