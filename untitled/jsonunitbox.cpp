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
    setFixedWidth(defaultWidth);
    setMinimumHeight(defaultHeight);

    QFont font;
    font.setPixelSize(20);
    setFont(font);
    QFontMetrics fm(font);
    QString newText = "", lineString = "";
    for(int i = 0; i < text.length(); i++) {
        if(text[i].unicode() == 10) {
            newText += lineString + "\n" ;
            lineString = "";
        }else {
            if(fm.width(lineString + text[i]) >= width() - 20) {
                newText += lineString + "\n";
                lineString = "";
            }
            lineString += text[i];
        }
    }
    newText += lineString;
    setText(newText);

    if(parent) {
        layout = dynamic_cast <QVBoxLayout *>(parent->layout());
    }
    QObject::connect(this, &JsonUnitBox::pressed, [=]() {
        printPath();
        if(subBox) {
            if(subBox->isVisible()) {
                //subBox->setVisible(false);
                //dynamic_cast <ContentBox *>(parent)->resizeBySizeHint(true);
                layout->removeWidget(subBox);
                subBox->setVisible(false);
            }else {
                if(subBox->getBoxNumber() != 0) {
                    layout->insertWidget(layout->indexOf(this) + 1, subBox);
                    subBox->setVisible(true);
                }

                //dynamic_cast <ContentBox *>(parent)->resizeBySizeHint(false);
            }

        //JsonUnitBox *newBox = new JsonUnitBox("box");
        }
    });

}

void JsonUnitBox::addSubBox(const QJsonValue &json) {

    if(!layout)
        return;
    subBox = new ContentBox(json, parentWidget());
    subBox->setParentBox(this);
    //layout->insertWidget(layout->indexOf(this) + 1, subBox);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    subBox->setVisible(false);

    //dynamic_cast <ContentBox *>(parentWidget())->resizeBySizeHint(false);
}


//Public Slots
void JsonUnitBox::printPath() {

    ContentBox *parentBox = dynamic_cast <ContentBox *>(parent());

    if(!parentBox->isBasedBox()) {
        parentBox->getParentBox()->printPath();
    }
    qDebug() << text();
}

void JsonUnitBox::setLayout(QVBoxLayout *layout) {
    this->layout = layout;
}
