#ifndef WINDOW_H
#define WINDOW_H

#include "jsonunitbox.h"

#include <QWidget>
#include <QLinkedList>

class Window : public QWidget {

    QLinkedList<JsonUnitBox *> *buttonList;

    public:
        Window(QWidget *parent = 0);



};



#endif // WINDOW_H

