TEMPLATE = app
TARGET = Filter

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

SOURCES += \
    main.cpp \
    window.cpp \
    jsonunitbox.cpp

DISTFILES += \
    json.txt

HEADERS += \
    window.h \
    jsonunitbox.h

