#include <iostream>

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QWidget>
#include <QStyle>

#include "window.h"

using namespace std;

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

/*
    QFile file("/json.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File cannot be opened";
    }else {
        while(!file.atEnd()) {
            QString line = file.readLine();
            qDebug() << line;
        }
    }
    file.close();
*/

    QWidget *window = new QWidget;
    window->setFixedSize(800, 600);

    QWidget *content = new QWidget(window);
    content->setFixedWidth(800 - window->style()->pixelMetric(QStyle::PM_ScrollBarExtent) - 2);

    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);

    content->setAutoFillBackground(true);
    content->setPalette(pal);

    QVBoxLayout *layout = new QVBoxLayout;

    //set the layout to the center.
    layout->setContentsMargins((content->width() - JsonUnitBox::DEFAULT_WIDTH) / 2, 10, (content->width() - JsonUnitBox::DEFAULT_WIDTH) / 2, 10);
    content->setLayout(layout);
    for(int i = 0; i < 2; i++) {
        JsonUnitBox *box = new JsonUnitBox("box" + QString::number(i), content);
        layout->addWidget(box);
    }

    QScrollArea *scroll = new QScrollArea(window);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scroll->setFixedSize(800, window->height());
    scroll->setWidget(content);

    window->show();


    app.exec();

}
