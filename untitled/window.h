#ifndef WINDOW_H
#define WINDOW_H

#include "jsonunitbox.h"

#include <QWidget>
#include <QLinkedList>
#include <QVBoxLayout>
#include <QScrollArea>

class ContentBox;
class QSize;
class Window : public QWidget {

    ContentBox *content;
    QScrollArea *scroll;

    public:
        Window(QWidget *parent = 0);

        void addContentBox(ContentBox *content);
        ContentBox *getContentBox();
        QScrollArea *getScroll();

};

class ContentBox : public QWidget {

    Q_OBJECT

    QVBoxLayout *layout;
    QScrollArea *scroll;
    bool isBased;
    QSize defaultSize;

    public:
        ContentBox(QWidget *parent = 0);
        ContentBox(QScrollArea *scroll, QWidget *parent = 0);

        bool isBasedBox();
        void setBasedBox(bool flag);

        void resizeBySizeHint(bool isDefault);
        void insertButton(int index);

    public slots:
        void addButton();

    private:
        int index;

};
/*
class SubBox : public ContentBox {

    Q_OBJECT

    bool buttonAdd;

    public:
        SubBox(ContentBox *parent = 0);

        bool isButtonAdd();

    private slots:
        void display();

};
*/


#endif // WINDOW_H

