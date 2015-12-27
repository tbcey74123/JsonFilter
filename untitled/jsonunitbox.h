#ifndef JSONUNITBOX_H
#define JSONUNITBOX_H

#include <QWidget>

#include <QPushButton>

class QPushButton;
class QVBoxLayout;
class SubBox;

class JsonUnitBox : public QPushButton {

    Q_OBJECT



    QVBoxLayout *layout;
    SubBox *subBox;

    public:
        const int static DEFAULT_WIDTH = 700, DEFAULT_HEIGHT = 50;

        JsonUnitBox(QWidget *parent = 0);
        JsonUnitBox(const QString &text, QWidget *parent = 0);

        void setLayout(QVBoxLayout *layout);
        void setSubBox(SubBox *box);

    private slots:
        void buttonPressed();

};

#endif // JSONUNITBOX_H
