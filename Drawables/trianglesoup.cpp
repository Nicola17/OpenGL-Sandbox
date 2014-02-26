#include "trianglesoup.h"
#include <QGLWidget>

TriangleSoup::TriangleSoup()
{
    _color[0] = 1.0;
    _color[1] = 0.5;
    _color[2] = 0.;
}

void TriangleSoup::draw()const{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &(_vertices[0]));
    glNormalPointer(GL_FLOAT, 0, &(_normals[0]));
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, _color);
    glDrawArrays(GL_TRIANGLES,0,_vertices.size());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void TriangleSoup::addTriangle(const vector_type& v0,const vector_type& v1,const vector_type& v2){
    _vertices.push_back(v0);
    _vertices.push_back(v1);
    _vertices.push_back(v2);
    const vector_type normal = vector_type::normal(v1-v0,v2-v0);
    _normals.push_back(normal);
    _normals.push_back(normal);
    _normals.push_back(normal);
}
void TriangleSoup::addTriangle(const vector_type& v0,const vector_type& v1,const vector_type& v2, const vector_type& n0,const vector_type& n1,const vector_type& n2){
    _vertices.push_back(v0);
    _vertices.push_back(v1);
    _vertices.push_back(v2);
    _normals.push_back(n0);
    _normals.push_back(n1);
    _normals.push_back(n2);
}
