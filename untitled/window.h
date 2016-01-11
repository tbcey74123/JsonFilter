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

class Window : public QWidget {

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

        static QJsonValue readJsonFile(QString filePath);

    private:
        void createControlPanel(Window *window);

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

