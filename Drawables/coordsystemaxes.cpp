#include "coordsystemaxes.h"
#include <QGLWidget>
#include "gl/GL.h"

CoordSystemAxes::CoordSystemAxes():
    _length(1.),
    _thickness(2)
{
}

void CoordSystemAxes::draw()const{
    glLineWidth(5);
    glEnable(GL_COLOR_MATERIAL);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0,0,0);
    glVertex3f(_length,0,0);
    glColor3f(0, 1, 0);
    glVertex3f(0,0,0);
    glVertex3f(0,_length,0);
    glColor3f(0, 0, 1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,_length);
    glEnd();
    glDisable(GL_COLOR_MATERIAL);
}
