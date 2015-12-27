#ifndef WINDOW_H
#define WINDOW_H

#include "jsonunitbox.h"

#include <QWidget>
#include <QLinkedList>
#include <QVBoxLayout>
#include <QScrollArea>

class Window : public QWidget {

    QLinkedList<JsonUnitBox *> *buttonList;

    public:
        Window(QWidget *parent = 0);

};

class ContentBox : public QWidget {

    Q_OBJECT

    QLinkedList<JsonUnitBox *> *buttonList;
    QVBoxLayout *vBox;
    QScrollArea *scroll;

    public:
        ContentBox();
        ContentBox(QScrollArea *scroll, QWidget *parent = 0);

        void insertButton(int index);

    public slots:
        void addButton();

    private:
        int index;
};

class SubBox : public ContentBox {

    Q_OBJECT

    bool buttonAdd;

    public:
        SubBox(ContentBox *parent = 0);

        bool isButtonAdd();

    private slots:
        void display();

};



#endif // WINDOW_H

