TEMPLATE = app
TARGET = camera

QT += multimedia multimediawidgets

HEADERS = \
    camera.h \
    common.h \
    menuwindow.h \
    photosviewerwindow.h \
    settingwindow.h \
    singlephotoviewerwindow.h \
    systeminfowindow.h \
    timesettingwindow.h \
    videosviewerwindow.h

SOURCES = \
    common.cpp \
    main.cpp \
    camera.cpp \
    menuwindow.cpp \
    photosviewerwindow.cpp \
    settingwindow.cpp \
    singlephotoviewerwindow.cpp \
    systeminfowindow.cpp \
    timesettingwindow.cpp \
    videosviewerwindow.cpp

FORMS += \
    camera.ui \
    menuwindow.ui \
    photosviewerwindow.ui \
    settingwindow.ui \
    singlephotoviewerwindow.ui \
    systeminfowindow.ui \
    timesettingwindow.ui \
    videosviewerwindow.ui

RESOURCES += camera.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/multimediawidgets/camera
INSTALLS += target

QT+=widgets
include(../../multimedia/shared/shared.pri)
