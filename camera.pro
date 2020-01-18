TEMPLATE = app
TARGET = camera

QT += multimedia multimediawidgets

HEADERS = \
    camera.h \
    common.h \
    databasewindow.h \
    menuwindow.h \
    newmedicalrecord.h \
    photosviewerwindow.h \
    settingwindow.h \
    singlephotoviewerwindow.h \
    systeminfowindow.h \
    timesettingwindow.h \
    toast.h \
    topbarwindow.h \
    videosviewerwindow.h \
    videoviewerwindow.h

SOURCES = \
    common.cpp \
    databasewindow.cpp \
    main.cpp \
    camera.cpp \
    menuwindow.cpp \
    newmedicalrecord.cpp \
    photosviewerwindow.cpp \
    settingwindow.cpp \
    singlephotoviewerwindow.cpp \
    systeminfowindow.cpp \
    timesettingwindow.cpp \
    toast.cpp \
    topbarwindow.cpp \
    videosviewerwindow.cpp \
    videoviewerwindow.cpp

FORMS += \
    camera.ui \
    databasewindow.ui \
    menuwindow.ui \
    newmedicalrecord.ui \
    photosviewerwindow.ui \
    settingwindow.ui \
    singlephotoviewerwindow.ui \
    systeminfowindow.ui \
    timesettingwindow.ui \
    toast.ui \
    topbarwindow.ui \
    videosviewerwindow.ui \
    videoviewerwindow.ui

RESOURCES += camera.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/multimediawidgets/camera
INSTALLS += target

INCLUDEPATH += /usr/local/include \
/usr/local/include/opencv4 \
/usr/local/include/opencv4/opencv2

LIBS += /usr/local/lib/libopencv_*

QT+=widgets
#include(../../multimedia/shared/shared.pri)
