#include "trianglesoup.h"
#include <QGLWidget>
#include <QMessageBox>

TriangleSoup::TriangleSoup():
    _color(255,150,0)
{

}

void TriangleSoup::initialize(){
    if(_normals.size()==0 || _vertices.size() == 0)
        return;

    if(!_program.addShaderFromSourceFile(QGLShader::Vertex,"F:\\Development\\OpenGLSandbox\\sources\\VertexShaders\\firsttest.vert"))
        throw std::runtime_error("Unable to compile the vertex shader");
    if(!_program.addShaderFromSourceFile(QGLShader::Fragment,"F:\\Development\\OpenGLSandbox\\sources\\FragmentShaders\\firsttest.frag"))
        throw std::runtime_error("Unable to compile the fragment shader");
    _program.link();

    _program.bind();
        _vao.bind();
            _verticesVbo.create();
            _verticesVbo.setUsagePattern(QGLBuffer::StaticDraw);
            _verticesVbo.bind();
                _verticesVbo.allocate(&(_vertices[0]),_vertices.size()*sizeof(vector_type));
            _verticesVbo.release();

            _normalsVbo.create();
            _normalsVbo.setUsagePattern(QGLBuffer::StaticDraw);
            _normalsVbo.bind();
                _verticesVbo.allocate(&(_normals[0]),_normals.size()*sizeof(vector_type));
            _normalsVbo.release();
        _vao.release();

    _program.release();
}

void TriangleSoup::draw()const{
    _program.bind();
    _vao.bind();
        _verticesVbo.bind();
            _program.enableAttributeArray("VertexPosition");
            _program.setAttributeBuffer("VertexPosition", GL_FLOAT, 0, 3 );
        _verticesVbo.release();

        _normalsVbo.bind();
            _program.enableAttributeArray("VertexNormal");
            _program.setAttributeBuffer("VertexNormal", GL_FLOAT, 0, 3 );
        _normalsVbo.release();
    glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
    _vao.release();
    _program.release();

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
