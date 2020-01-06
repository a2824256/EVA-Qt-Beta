TEMPLATE = app
TARGET = camera

QT += multimedia multimediawidgets

HEADERS = \
    camera.h \
    menuwindow.h \
    settingwindow.h \
    systeminfowindow.h \
    timesettingwindow.h

SOURCES = \
    main.cpp \
    camera.cpp \
    menuwindow.cpp \
    settingwindow.cpp \
    systeminfowindow.cpp \
    timesettingwindow.cpp

FORMS += \
    camera.ui \
    menuwindow.ui \
    settingwindow.ui \
    systeminfowindow.ui \
    timesettingwindow.ui

RESOURCES += camera.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/multimediawidgets/camera
INSTALLS += target

QT+=widgets
include(../../multimedia/shared/shared.pri)
