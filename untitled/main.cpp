#include <iostream>

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QWidget>

using namespace std;

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

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

    return 0;
}
