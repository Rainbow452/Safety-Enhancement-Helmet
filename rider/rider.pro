#-------------------------------------------------
#
# Project created by QtCreator 2022-03-17T20:31:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rider
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    yolo-fastestv2.cpp \
    mythread.cpp \
    awake_dectectthread.cpp \
    video_photo.cpp

HEADERS += \
        widget.h \
    yolo-fastestv2.h \
    mythread.h \
    audiorecoding.h \
    awake_dectectthread.h \
    video_photo.h

FORMS += \
        widget.ui
INCLUDEPATH +=/usr/local/include\
   /usr/local/include/opencv4\
   /usr/local/include/opencv4/opencv2\
   /home/pi/ncnn/build/install/include/ncnn

LIBS +=/usr/local/lib/libopencv_*.so\
       /home/pi/ncnn/build/install/lib/libncnn.a
QMAKE_CXXFLAGS += -fopenmp
LIBS +=-ldl
LIBS += -fopenmp


DISTFILES +=\
    model/yolo-fastestv2-opt.bin \
    model/yolo-fastestv2-opt.param
