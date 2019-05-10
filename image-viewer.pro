#-------------------------------------------------
#
# Project created by QtCreator 2018-08-15T16:53:51
#
#-------------------------------------------------

QT       += core gui widgets concurrent

TARGET = image-viewer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    model/filesystemmanager.cpp \
    model/image.cpp \
    model/imagelist.cpp \
    model/imageviewer.cpp \
    ui/loadingdialog.cpp \
    ui/mainwindow.cpp \
    main.cpp

HEADERS += \
    model/filesystemmanager.h \
    model/image.h \
    model/imagelist.h \
    model/imageviewer.h \
    ui/loadingdialog.h \
    ui/mainwindow.h

FORMS += \
    ui/loadingdialog.ui \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

win32:RC_ICONS += images/Picture-Viewer-icon.ico
