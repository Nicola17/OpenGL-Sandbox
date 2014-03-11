#include "trianglesoup.h"
#include <QGLWidget>
#include <QGLShader>
#include <QGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QGLBuffer>

TriangleSoup::TriangleSoup():
    _color(255,150,0)
{

}

void TriangleSoup::draw()const{
    if(_normals.size()==0 || _vertices.size() == 0)
        return;
/*
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &(_vertices[0]));
    glNormalPointer(GL_FLOAT, 0, &(_normals[0]));
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, _color);
    glDrawArrays(GL_TRIANGLES,0,_vertices.size());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
*/

    QGLShaderProgram program;
    if(!program.addShaderFromSourceFile(QGLShader::Vertex,"F:\\Development\\OpenGLSandbox\\sources\\VertexShaders\\firsttest.vert"))
        throw std::runtime_error("Unable to compile the vertex shader");
    if(!program.addShaderFromSourceFile(QGLShader::Fragment,"F:\\Development\\OpenGLSandbox\\sources\\FragmentShaders\\firsttest.frag"))
        throw std::runtime_error("Unable to compile the fragment shader");
    program.link();

    QOpenGLVertexArrayObject vao;
    QGLBuffer verticesVbo;
    QGLBuffer normalsVbo;

    vao.bind();
        verticesVbo.create();
        verticesVbo.setUsagePattern(QGLBuffer::StaticDraw);
        verticesVbo.bind();
            verticesVbo.allocate(&(_vertices[0]),_vertices.size()*sizeof(vector_type));
            program.enableAttributeArray("VertexPosition");
            program.setAttributeBuffer("VertexPosition", GL_FLOAT, 0, 3 );
        verticesVbo.release();

        normalsVbo.create();
        normalsVbo.setUsagePattern(QGLBuffer::StaticDraw);
        normalsVbo.bind();
            verticesVbo.allocate(&(_normals[0]),_normals.size()*sizeof(vector_type));
            program.enableAttributeArray("VertexNormal");
            program.setAttributeBuffer("VertexNormal", GL_FLOAT, 0, 3 );
        normalsVbo.release();
    vao.release();


    program.bind();
    vao.bind();

/*
    int vertexLocation = program.attributeLocation("VertexPosition");
    program.enableAttributeArray(vertexLocation);
    program.setAttributeArray(vertexLocation,&(_vertices[0]),0);
    program.bindAttributeLocation("VertexPosition",vertexLocation);

    int normalLocation = program.attributeLocation("VertexNormal");
    program.enableAttributeArray(normalLocation);
    program.setAttributeArray(normalLocation,&(_normals[0]),0);
    program.bindAttributeLocation("VertexNormal",normalLocation);
*/
    glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
    //glDrawArrays(GL_TRIANGLES, 0, _normals.size());
/*
    program.disableAttributeArray(vertexLocation);
    program.disableAttributeArray(normalLocation);
*/
    vao.release();
    program.release();

/*
    GLuint vaoId;
    glGenVertexArrays(1,&vaoId);
    glBindVertexArray(vaoId);

    GLuint vboId[2];
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices::value_type)*_vertices.size(), &(_vertices[0]), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
*/

    /*
    program.bind();
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &(_vertices[0]));
    glNormalPointer(GL_FLOAT, 0, &(_normals[0]));
    glColor3f(_color.redF(), _color.greenF(), _color.blueF());
    glDrawArrays(GL_TRIANGLES,0,_vertices.size());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    program.release();
    */

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
