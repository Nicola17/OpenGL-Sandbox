#ifndef HELLOWORLDWINDOW_H
#define HELLOWORLDWINDOW_H

#include "openglwindow.h"
#include <QtGui/QOpenGLShaderProgram>

class HelloWorldWindow : public OpenGLWindow
{
public:
    HelloWorldWindow();

    void initialize();
    void render();

private:
    GLuint loadShader(GLenum type, const char *source);

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;
    int m_frame;
};

#endif // HELLOWORLDWINDOW_H
