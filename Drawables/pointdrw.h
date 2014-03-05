#ifndef POINTDRW_H
#define POINTDRW_H

#include <QVector3D>
#include <QColor>
#include "drawableintrfc.h"

class PointDrw: public DrawableIntrfc
{
public:
    PointDrw();
    virtual ~PointDrw(){}
    virtual void draw()const;

    QVector3D& point(){return _point;}
    const QVector3D& point()const{return _point;}
    QColor& color(){return _color;}
    const QColor& color()const{return _color;}
    float& size(){return _size;}
    const float& size()const{return _size;}

private:
    QVector3D   _point;
    QColor      _color;
    float       _size;
};

#endif // POINTDRW_H
