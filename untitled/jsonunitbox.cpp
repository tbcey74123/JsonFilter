#include "jsonunitbox.h"

#define defaultWidth  700
#define defaultHeight 50

#include <QWidget>
#include <QLinkedList>
#include <QPalette>

JsonUnitBox::JsonUnitBox(QWidget *parent) : JsonUnitBox("", parent) {}

JsonUnitBox::JsonUnitBox(const QString &text, QWidget *parent) : QPushButton(text, parent) {

    setFixedSize(defaultWidth, defaultHeight);


}

