#include <iostream>

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QWidget>
#include <QStyle>
#include <QJsonDocument>
#include <QJsonValue>
#include <QDir>
#include <QLabel>\

#include "window.h"

using namespace std;

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    QFile file("../untitled/json2.txt");
    QString line;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File cannot be opened";
    }else {

        while(!file.atEnd()) {
            line = file.readLine();
            //qDebug() << line;
        }
    }
    file.close();

    QJsonValue json = QJsonValue::fromVariant(QJsonDocument::fromJson(line.toUtf8()).toVariant());
    Window *window = new Window;
    //window->init(json);
    window->show();

    app.exec();
}


