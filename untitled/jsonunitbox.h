#ifndef JSONUNITBOX_H
#define JSONUNITBOX_H

#include <QWidget>

#include <QPushButton>


class QPushButton;

class JsonUnitBox : public QPushButton {

    public:
        JsonUnitBox(QWidget *parent = 0);
        JsonUnitBox(const QString &text, QWidget *parent = 0);

};

#endif // JSONUNITBOX_H
