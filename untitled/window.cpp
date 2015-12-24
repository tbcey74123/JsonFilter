#include "window.h"
#include "jsonunitbox.h"

#include <QWidget>
#include <QPalette>
#include <QVBoxLayout>
#include <QPushButton>


#define maxWidth 800
#define maxHeight 600

Window::Window(QWidget *parent) : QWidget(parent) {

   setFixedSize(maxWidth, maxHeight);
\
   buttonList = new QLinkedList<JsonUnitBox *>();
   QVBoxLayout *vBox = new QVBoxLayout;
   vBox->setMargin(50);
   vBox->setSpacing(5);

   for(int i = 0; i < 10; i++) {
       JsonUnitBox *newButton = new JsonUnitBox("box", this);
       buttonList->append(newButton);
       vBox->addWidget(newButton);
   }


   setLayout(vBox);

   /*QWidget *test = new QWidget(this);
   test->setGeometry(100, 100, 100, 100);
   QPalette Pal(test->palette());
   Pal.setColor(QPalette::Background, Qt::black);
   test->setAutoFillBackground(true);
   test->setPalette(Pal);*/


}
