#include "window.h"
#include "jsonunitbox.h"

#include <QDebug>
#include <QWidget>
#include <QPalette>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QTextBrowser>
#include <QStyle>
#include <QJsonDocument>
#include <QJSonObject>
#include <QJsonArray>
#include <QGroupBox>
#include <QFile>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#define maxWidth 800
#define maxHeight 600

Window::Window(QWidget *parent) : QWidget(parent) {

   manager = new QNetworkAccessManager(this);
   QObject::connect(manager, &QNetworkAccessManager::finished, this, &Window::requestFinished);

   content = NULL;
   setFixedSize(maxWidth, maxHeight);
   createControlPanel(this);

   scroll = new QScrollArea(this);
   //scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

   layout = new QVBoxLayout;
   layout->addWidget(controlPanel);
   layout->addWidget(scroll);

   setLayout(layout);
}

void Window::init() {
    if(content) {
        delete content;
    }
    if(scroll) {
        delete scroll;
        scroll = new QScrollArea(this);
        layout->addWidget(scroll);
    }
    content = NULL;
}

void Window::init(const QJsonValue &json) {

    if(content) {
        delete content;
    }

    content = new ContentBox(json, this);
    content->setBasedBox(true);
    scroll->setWidget(content);
}

ContentBox *Window::getContentBox() { return content; }
QScrollArea *Window::getScroll() { return scroll; }



void Window::handleInput(QString input) {

    if(input.startsWith("http")) {
        manager->get(QNetworkRequest(QUrl(input)));
    }else {
        QJsonValue json = readJsonFile(input);
        if(json != NULL)
            init(json);
    }
}

QJsonValue Window::readJsonFile(QString filePath) {

    QFile file(filePath);
    QString line;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File cannot be opened";
        return NULL;
    }else {
        while(!file.atEnd()) {
            line = file.readLine();
            //qDebug() << line;
        }
    }
    file.close();

    QJsonValue json = QJsonValue::fromVariant(QJsonDocument::fromJson(line.toUtf8()).toVariant());
    return json;
}

//Privete function for Window
void Window::createControlPanel(Window *window) {
    controlPanel = new QGroupBox;
    controlPanel->setFixedHeight(200);
    QGridLayout *layout = new QGridLayout;

    QLineEdit *filePathInput = new QLineEdit;

    QPushButton *button1 = new QPushButton("read");
    QPushButton *button2 = new QPushButton("init");

    QObject::connect(filePathInput, &QLineEdit::returnPressed, [=]() {
        button1->pressed();
    });

    QObject::connect(button1, &QPushButton::pressed, [=]() {
        handleInput(filePathInput->text());
    });
    QObject::connect(button2, &QPushButton::pressed, [=]() {
        window->init();
    });

    layout->addWidget(filePathInput, 0, 0, 1, 4);
    layout->addWidget(button1, 1, 0, 1, 2);
    layout->addWidget(button2, 1, 2, 1, 2);

    controlPanel->setLayout(layout);
}

//Private slots
void Window::requestFinished(QNetworkReply *reply) {


    QJsonValue json = QJsonValue::fromVariant(QJsonDocument::fromJson(reply->readAll()).toVariant());
    if(json != NULL)
        init(json);
    //qDebug() << json;
}



ContentBox::ContentBox(const QJsonValue &json, QWidget *parent) : QWidget(parent){

    //setFixedWidth(parent->width() - parent->style()->pixelMetric(QStyle::PM_ScrollBarExtent) - 2);
    //setFixedWidth(600);

    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);

    setAutoFillBackground(true);
    //setPalette(pal);

    layout = new QVBoxLayout;

    //set the layout to the center.
    //layout->setContentsMargins((width() - JsonUnitBox::DEFAULT_WIDTH) / 2, 10, (width() - JsonUnitBox::DEFAULT_WIDTH) / 2, 10);
    layout->setContentsMargins(30, 10, 30, 10);
    setLayout(layout);

    handleJson(json);
    boxNumber = layout->count();
}

bool ContentBox::isBasedBox() { return isBased; }
void ContentBox::setBasedBox(bool flag) { isBased = flag; }

JsonUnitBox *ContentBox::getParentBox() { return parentBox; }
void ContentBox::setParentBox(JsonUnitBox *parentBox) {
    this->parentBox = parentBox;
}

int ContentBox::getBoxNumber() { return boxNumber; }

void ContentBox::resizeBySizeHint(bool isDefault) {

    qDebug() << "tset";
    if(isDefault) {
        setFixedSize(defaultSize);
        setMinimumSize(defaultSize);
    }
    else
        setMinimumSize(sizeHint());

    if(parent() && !isBased) {
        ContentBox *p = dynamic_cast <ContentBox *>(parent());
        p->resizeBySizeHint(isDefault);
    }
}

void ContentBox::handleJson(const QJsonValue &json) {

    if(json.isNull() || json.isUndefined()) return;
    if(json.isObject()) {
       QJsonObject obj = json.toObject();
       for(QJsonObject::Iterator i = obj.begin(); i != obj.end(); ++i) {
           JsonUnitBox *button = addButton(i.key());
           button->addSubBox(i.value());
       }
    }else if(json.isArray()) {

        QJsonArray arr = json.toArray();
        for(int i = 0; i < arr.size(); i++) {
            JsonUnitBox *button = addButton("[" + QString::number(i) + "]");
            button->addSubBox(arr.at(i));
        }
    }else {
        addButton(json.toVariant().toString());
    }


}

void ContentBox::init() {
    layout = new QVBoxLayout;

    layout->setContentsMargins(30, 10, 30, 10);
    setLayout(layout);
}


//public slots
JsonUnitBox *ContentBox::addButton() {
    return addButton(" ");
}
JsonUnitBox *ContentBox::addButton(const QString &text) {


    JsonUnitBox *newBox = new JsonUnitBox(text, this);
    layout->addWidget(newBox);

    return newBox;
}

