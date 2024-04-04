QT       += core gui

QT += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog.cpp \
    main.cpp \
    nota.cpp \
    utils.cpp \
    widget.cpp

HEADERS += \
    dialog.h \
    main.h \
    nota.h \
    utils.h \
    widget.h

FORMS += \
    dialog.ui \
    nota.ui \
    widget.ui

# Default rules for deployment.

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
RC_ICONS = universidad.ico
DISTFILES += \
    ../Data/Asignaturas.xml \
    Data/Asignaturas.xml
