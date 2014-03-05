#ifndef LINEDRW_H
#define LINEDRW_H

#include <QVector3D>
#include <QColor>
#include "drawableintrfc.h"

class LineDrw: public DrawableIntrfc
{
public:
    LineDrw();
    virtual ~LineDrw(){}
    virtual void draw()const;

    QVector3D& p0(){return _p0;}
    const QVector3D& p0()const{return _p0;}
    QVector3D& p1(){return _p1;}
    const QVector3D& p1()const{return _p1;}
    QColor& color(){return _color;}
    const QColor& color()const{return _color;}
    float& thickness(){return _thickness;}
    const float& thickness()const{return _thickness;}

private:
    QVector3D   _p0;
    QVector3D   _p1;
    QColor      _color;
    float       _thickness;
};

#endif // LINEDRW_H
