QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DESTDIR = ./bin
MOC_DIR = ./temp/moc_dir
RCC_DIR = ./temp/rcc_dir
OBJECTS_DIR = ./temp/obj_dir
UI_DIR = ./temp/ui_dir

INCLUDEPATH += src

SOURCES += \
    src/AttitudeIndicator.cpp \
    src/AzimuthAngleWidget.cpp \
    src/BodyForm.cpp \
    src/CloseCombatForm.cpp \
    src/CompassWidget.cpp \
    src/CustomGraphicsView.cpp \
    src/GyroForm.cpp \
    src/OrientationForm.cpp \
    src/StatusForm.cpp \
    src/main.cpp \
    src/MainForm.cpp \
    src/TimerWorker.cpp

HEADERS += \
    src/AttitudeIndicator.h \
    src/AzimuthAngleWidget.h \
    src/BodyForm.h \
    src/CloseCombatForm.h \
    src/CompassWidget.h \
    src/CustomGraphicsView.h \
    src/GyroForm.h \
    src/MainForm.h \
    src/OrientationForm.h \
    src/StatusForm.h \
    src/TimerWorker.h

FORMS += \
    forms/MainForm.ui \
    forms/StatusForm.ui \
    forms/GyroForm.ui \
    forms/BodyForm.ui \
    forms/OrientationForm.ui \
    forms/CloseCombatForm.ui \
    forms/AttitudeIndicator.ui \
    forms/CompassWidget.ui \
    forms/AzimuthAngleWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image_qrc.qrc
