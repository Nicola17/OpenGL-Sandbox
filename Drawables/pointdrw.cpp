#include "pointdrw.h"
#include <QGLWidget>
#include "gl/GL.h"

PointDrw::PointDrw():
    _point(0.2,0.2,0),
    _color(qRgb(1.0,0,0.0)),
    _size(1.0)
{
}

void PointDrw::draw()const{
    glPointSize(_size);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(_color.red(), _color.green(), _color.blue());
    glBegin(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glVertex3f(_point.x(),_point.y(),_point.z());
    glEnd();
    glEnd();
    glDisable(GL_COLOR_MATERIAL);
}

