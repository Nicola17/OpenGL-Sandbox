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

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMatrix4x4>
#include "Drawables/drawableintrfc.h"
#include "Utils/abstractlog.h"

class QtLogo;

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void addDrawableObject(const DrawableIntrfc* d);
    void removeDrawableObject(const DrawableIntrfc* d);
    void clear();
    void forceRepaint();
    void setBackgroundColor(QColor bgColor);
    void viewMatrix(QMatrix4x4& v);
    void projectionMatrix(QMatrix4x4& p);
    void setLight();

    void moveCamera(QVector3D& t);
    const QVector3D& cameraPosition()const{return _cameraPosition;}

    float& cameraSpeed(){return _cameraSpeed;}
    const float& cameraSpeed()const{return _cameraSpeed;}
    float& cameraRotationSpeed(){return _rotationSpeed;}
    const float& cameraRotationSpeed()const{return _rotationSpeed;}

    bool& showAxes(){return _showAxes;}
    const bool& showAxes()const{return _showAxes;}
    float& axesLength(){return _axesLength;}
    const float& axesLength()const{return _axesLength;}

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void onResetCameraPosition();

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent (QWheelEvent* event);

private:
    std::vector<const DrawableIntrfc*>_drawableObjects;
    int _xRot;
    int _yRot;
    int _zRot;
    float _rotationSpeed;

    float _cameraSpeed;
    float _cameraRadius;
    QVector3D _cameraPosition;

    QPoint lastPos;
    QColor _bgColor;

    bool _showAxes;
    float _axesLength;

public:
    AbstractLog*    _log;
    bool            _verbose;
};

#endif
