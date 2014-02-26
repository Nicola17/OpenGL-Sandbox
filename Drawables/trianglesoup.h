#ifndef TRIANGLESOUP_H
#define TRIANGLESOUP_H

#include <QVector3D>
#include "drawableintrfc.h"
#include <vector>
#include <QGLWidget>

class TriangleSoup: public DrawableIntrfc
{
public:
    typedef QVector3D vector_type;
    typedef std::vector<vector_type> vector_list_type;

public:
    TriangleSoup();
    virtual void draw()const;

    void addTriangle(const vector_type& v0,const vector_type& v1,const vector_type& v2);
    void addTriangle(const vector_type& v0,const vector_type& v1,const vector_type& v2,const vector_type& n0,const vector_type& n1,const vector_type& n2);

private:
    GLfloat _color[4];
    vector_list_type _vertices;
    vector_list_type _normals;
};

#endif // TRIANGLESOUP_H
