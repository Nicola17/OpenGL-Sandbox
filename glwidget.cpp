/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include <QtOpenGL>
#include <QMatrix4x4>
#include <math.h>

#include "glwidget.h"
#include "Drawables/qtlogo.h"
#include "Drawables/coordsystemaxes.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif


GLWidget::GLWidget(QWidget *parent):
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
    _bgColor(qRgb(112,128,144)),
    _log(nullptr),
    _verbose(false),
    _rotationSpeed(0.0625),
    _cameraSpeed(0.1),
    _cameraPosition(0,0,0)
{
    _xRot = 0;
    _yRot = 0;
    _zRot = 0;
}

GLWidget::~GLWidget()
{
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

void GLWidget::addDrawableObject(const DrawableIntrfc* d){
    auto it = std::find(_drawableObjects.begin(),_drawableObjects.end(),d);
    if(it == _drawableObjects.end())
        _drawableObjects.push_back(d);
}

void GLWidget::removeDrawableObject(const DrawableIntrfc* d){
    auto it = std::find(_drawableObjects.begin(),_drawableObjects.end(),d);
    if(it != _drawableObjects.end())
        _drawableObjects.erase(it);
}

void GLWidget::clear(){
    _drawableObjects.clear();
}

void GLWidget::forceRepaint(){
    updateGL();
}

void GLWidget::setBackgroundColor(QColor bgColor){
    SECURE_LOG(_log,"Set background color");
    _bgColor = bgColor;
    qglClearColor(_bgColor);
}
void GLWidget::viewMatrix(QMatrix4x4& vm){
    vm.translate(QVector3D(0,0,-10));
    vm.rotate(_xRot * _rotationSpeed, 1.0, 0.0, 0.0);
    vm.rotate(_yRot * _rotationSpeed, 0.0, 1.0, 0.0);
    vm.rotate(_zRot * _rotationSpeed, 0.0, 0.0, 1.0);
    vm.translate(_cameraPosition);
}
void GLWidget::projectionMatrix(QMatrix4x4& p){
    p.perspective(10,1,1,150);
}
 void GLWidget::moveCamera(QVector3D& t){
    _cameraPosition += t*_cameraSpeed;
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != _xRot) {
        _xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != _yRot) {
        _yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != _zRot) {
        _zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}
void GLWidget::initializeGL(){
    SECURE_LOG(_log,"Initialize GL");
    qglClearColor(_bgColor);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_MULTISAMPLE);
}

void GLWidget::setLight(){
    glEnable(GL_LIGHT0);
    QMatrix4x4 view;
    viewMatrix(view);

    QVector4D lightPosition(0, 4.0, 2.0, 1.0);
    //lightPosition = view * lightPosition;
    GLfloat lp[4] = { lightPosition.x(), lightPosition.y(), lightPosition.z(), lightPosition.w()};

    glLightfv(GL_LIGHT0, GL_POSITION, lp);
}
void GLWidget::paintGL(){
    SECURE_LOG_VERBOSE(_log,"Paint GL");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    QMatrix4x4 view;
    viewMatrix(view);
    for(auto dr: _drawableObjects){
        QMatrix4x4 model;
        QMatrix4x4 rtrx(view*model);
        glLoadMatrixf(rtrx.constData());
        dr->draw();
    }
    CoordSystemAxes coord;
    coord.draw();

    glMatrixMode(GL_PROJECTION);
    QMatrix4x4 projection;
    projectionMatrix(projection);
    glLoadMatrixf(projection.constData());

    setLight();
}
void GLWidget::resizeGL(int width, int height){
    SECURE_LOG(_log,"Resize GL");
    SECURE_LOG_VAL(_log,"Width",width);
    SECURE_LOG_VAL(_log,"Height",height);
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
}

void GLWidget::mousePressEvent(QMouseEvent *event){
    SECURE_LOG_VERBOSE(_log,"Mouse pressed");
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event){
    const int dx = event->x() - lastPos.x();
    const int dy = event->y() - lastPos.y();
    SECURE_LOG_VAL_VERBOSE(_log,"Dx",dx);
    SECURE_LOG_VAL_VERBOSE(_log,"Dy",dy);

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(_xRot + 8 * dy);
        setYRotation(_yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(_xRot + 8 * dy);
        setZRotation(_zRot + 8 * dx);
    }
    lastPos = event->pos();
}
void GLWidget::keyPressEvent(QKeyEvent *){
    SECURE_LOG_VERBOSE(_log,"Keyboard key pressed");
}
