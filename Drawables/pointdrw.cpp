#include "pointdrw.h"
#include <QGLWidget>
#include "gl/GL.h"

PointDrw::PointDrw():
    _point(0,0,0),
    _color(qRgb(1.0,0,1.0))
{
}

void PointDrw::draw()const{
    GLfloat vertex[3] = {_point.x(),_point.y(),_point.z()};
    GLfloat color[3] = {_color.red(),_color.green(),_color.blue()};

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glDrawArrays(GL_POINTS,0,1);
    glDisableClientState(GL_VERTEX_ARRAY);
}

