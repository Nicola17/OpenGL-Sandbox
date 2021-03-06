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
    Drawables/linedrw.h \
    Drawables/coordsystemaxes.h \
    Drawables/drawabletrimesh.h
SOURCES       = glwidget.cpp \
                main.cpp \
                mainwindow.cpp \
    Drawables/trianglesoup.cpp \
    Drawables/qtlogo.cpp \
    trianglesoupimporters.cpp \
    Utils/ptelog.cpp \
    Drawables/pointdrw.cpp \
    Drawables/linedrw.cpp \
    Drawables/coordsystemaxes.cpp \
    Drawables/drawabletrimesh.cpp
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

OTHER_FILES += \
    VertexShaders/firsttest.vert \
    FragmentShaders/firsttest.frag

win32:CONFIG(release, debug|release): LIBS += -L"$(SURFACE_MESH_LIB_DIR)/release/" -lsurface_mesh
else:win32:CONFIG(debug, debug|release): LIBS += -L"$(SURFACE_MESH_LIB_DIR)/debug/" -lsurface_mesh

INCLUDEPATH += "$(SURFACE_MESH_SRC_DIR)"
DEPENDPATH += "$(SURFACE_MESH_SRC_DIR)"

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += "$(SURFACE_MESH_LIB_DIR)/release/surface_mesh.lib"
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += "$(SURFACE_MESH_LIB_DIR)/debug/surface_mesh.lib"
