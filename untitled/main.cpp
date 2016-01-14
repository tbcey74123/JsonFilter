#include <iostream>

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QWidget>
#include <QStyle>
#include <QJsonDocument>
#include <QJsonValue>
#include <QDir>
#include <QLabel>
#include <QComboBox>

#include "window.h"

using namespace std;

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    Window *window = new Window;
    window->show();

    app.exec();
}


