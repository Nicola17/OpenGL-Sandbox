#include "linedrw.h"
#include <QGLWidget>
#include "gl/GL.h"

LineDrw::LineDrw():
    _p0(0,0,0),
    _p1(0,1,0),
    _color(qRgb(0.0,0.6,1.0)),
    _thickness(1.0)
{
}

void LineDrw::draw()const{
    glLineWidth(_thickness);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(_color.red(), _color.green(), _color.blue());
    glBegin(GL_LINES);
    glVertex3f(_p0.x(),_p0.y(),_p0.z());
    glVertex3f(_p1.x(),_p1.y(),_p1.z());
    glEnd();
    glDisable(GL_COLOR_MATERIAL);
}

