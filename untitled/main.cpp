#include <iostream>

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QWidget>
#include <QStyle>
#include <QJsonDocument>

#include "window.h"

using namespace std;



int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    QFile file("/json.txt");
    QString line;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File cannot be opened";
    }else {
        while(!file.atEnd()) {
            line = file.readLine();
            qDebug() << line;
        }
    }
    file.close();

    QJsonDocument json = QJsonDocument::fromJson(line.toUtf8());

    Window *window = new Window;
    window->show();

    //window->getContentBox()->handleJson(json);

    app.exec();
}


