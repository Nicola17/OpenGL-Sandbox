VPATH += shared
INCLUDEPATH += shared

HEADERS       = glwidget.h \
                qtlogo.h \
                mainwindow.h \
    drawableintrfc.h \
    Drawables/trianglesoup.h \
    Drawables/qtlogo.h \
    Drawables/drawableintrfc.h \
    trianglesoupimporters.h \
    Utils/abstractlog.h \
    Utils/ptelog.h \
    Drawables/pointdrw.h \
    Drawables/linedrw.h
SOURCES       = glwidget.cpp \
                main.cpp \
                mainwindow.cpp \
    Drawables/trianglesoup.cpp \
    Drawables/qtlogo.cpp \
    trianglesoupimporters.cpp \
    Utils/ptelog.cpp \
    Drawables/pointdrw.cpp \
    Drawables/linedrw.cpp
QT           += opengl widgets

# install
target.path = ./
INSTALLS += target


simulator: warning(This example might not fully work on Simulator platform)

contains(QT_CONFIG, opengles.) {
    contains(QT_CONFIG, angle): \
        warning("Qt was built with ANGLE, which provides only OpenGL ES 2.0 on top of DirectX 9.0c")
    error("This example requires Qt to be configured with -opengl desktop")
}

FORMS += \
    mainwindow.ui
