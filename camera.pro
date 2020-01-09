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
    videosviewerwindow.h \
    videoviewerwindow.h

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
    videosviewerwindow.cpp \
    videoviewerwindow.cpp

FORMS += \
    camera.ui \
    menuwindow.ui \
    photosviewerwindow.ui \
    settingwindow.ui \
    singlephotoviewerwindow.ui \
    systeminfowindow.ui \
    timesettingwindow.ui \
    videosviewerwindow.ui \
    videoviewerwindow.ui

RESOURCES += camera.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/multimediawidgets/camera
INSTALLS += target

#INCLUDEPATH += /usr/local/Cellar/opencv@3/3.4.9_1/include/opencv2
#INCLUDEPATH += /usr/local/Cellar/opencv@3/3.4.9_1/include
#INCLUDEPATH += /usr/local/include/
#INCLUDEPATH += /usr/local/opt/opencv@3/lib
INCLUDEPATH += /usr/local/include \
/usr/local/include/opencv4 \
/usr/local/include/opencv4/opencv2

LIBS += /usr/local/lib/libopencv_*
#LIBS += /usr/local/lib
#LIBS += -L/usr/local/Cellar/opencv@3/3.4.9_1/lib \
# -lopencv_core \
# -lopencv_highgui \
# -lopencv_imgproc \

QT+=widgets
#include(../../multimedia/shared/shared.pri)
