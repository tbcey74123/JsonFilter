#ifndef WINDOW_H
#define WINDOW_H

#include "jsonunitbox.h"

#include <QWidget>
#include <QLinkedList>
#include <QVBoxLayout>
#include <QScrollArea>

class QGroupBox;
class ContentBox;
class QSize;
class QNetworkReply;
class QNetworkAccessManager;

class Window : public QWidget {

    Q_OBJECT

    QNetworkAccessManager *manager;

    ContentBox *content;
    QScrollArea *scroll;
    QGroupBox *controlPanel;
    QVBoxLayout *layout;

    public:
        Window(QWidget *parent = 0);

        void init();
        void init(const QJsonValue &json);
        void addContentBox(ContentBox *content);

        ContentBox *getContentBox();
        QScrollArea *getScroll();

        void handleInput(QString input);
        static QJsonValue readJsonFile(QString filePath);

    private:
        void createControlPanel(Window *window);


    private slots:
        void requestFinished(QNetworkReply *reply);

};

class ContentBox : public QWidget {

    Q_OBJECT

    QVBoxLayout *layout;
    QScrollArea *scroll;
    bool isBased;
    QSize defaultSize;
    JsonUnitBox *parentBox;

    public:
        ContentBox(const QJsonValue &json, QWidget *parent = 0);
        ContentBox(QScrollArea *scroll, QWidget *parent = 0);

        bool isBasedBox();
        void setBasedBox(bool flag);
        JsonUnitBox *getParentBox();
        void setParentBox(JsonUnitBox *parentBox);

        int getBoxNumber();

        void resizeBySizeHint(bool isDefault);
        void insertButton(int index);
        void handleJson(const QJsonValue &json);

        void init();

    public slots:
        JsonUnitBox *addButton();
        JsonUnitBox *addButton(const QString &text);

    private:
        int index;
        int boxNumber;



};

#endif // WINDOW_H

