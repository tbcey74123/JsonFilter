#ifndef JSONUNITBOX_H
#define JSONUNITBOX_H

#include <QWidget>

#include <QPushButton>

class QPushButton;
class QVBoxLayout;

class ContentBox;
class JsonUnitBox : public QPushButton {

    Q_OBJECT

    QVBoxLayout *layout;
    ContentBox *subBox;

    public:
        const int static DEFAULT_WIDTH = 500, DEFAULT_HEIGHT = 50;

        JsonUnitBox(QWidget *parent = 0);
        JsonUnitBox(const QString &text, QWidget *parent = 0);

        void setLayout(QVBoxLayout *layout);

    private slots:
};

#endif // JSONUNITBOX_H
