#include "window.h"
#include "jsonunitbox.h"

#include <QWidget>
#include <QPalette>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QTextBrowser>

#define maxWidth 800
#define maxHeight 600

Window::Window(QWidget *parent) : QWidget(parent) {

   setFixedSize(maxWidth, maxHeight);
   //setMinimumSize(maxWidth, maxHeight);

   buttonList = new QLinkedList<JsonUnitBox *>();

   QScrollArea *scroll = new QScrollArea(this);
   QVBoxLayout *vBox = new QVBoxLayout(scroll);

   //vBox->setMargin(50);
   //vBox->setSpacing(50);

   for(int i = 0; i < 5; i++) {
       JsonUnitBox *newButton = new JsonUnitBox("box", this);
       buttonList->append(newButton);
       vBox->addWidget(newButton);
   }

   setLayout(vBox);


   scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
   scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   scroll->resize(700, 400);
   scroll->setWidgetResizable(false);
   scroll->setWidget(vBox->widget());


}
