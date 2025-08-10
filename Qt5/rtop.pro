QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    dialog.cpp

HEADERS += \
    dialog.h \
    rtop_rust.h

FORMS += \
    dialog.ui

# Link with the Rust library
win32: LIBS += -L$PWD/../cpu_monitor/target/release -lcpu_monitor
else:unix: LIBS += -L$PWD/../cpu_monitor/target/release -lcpu_monitor

INCLUDEPATH += $PWD/../cpu_monitor/src
DEPENDPATH += $PWD/../cpu_monitor/src


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
