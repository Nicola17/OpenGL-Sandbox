#ifndef COORDSYSTEMAXES_H
#define COORDSYSTEMAXES_H

#include "drawableintrfc.h"

class CoordSystemAxes: public DrawableIntrfc
{
public:
    CoordSystemAxes();
    virtual ~CoordSystemAxes(){}
    virtual void draw()const;

public:
    float& length(){return _length;}
    const float& length()const{return _length;}
    float& thickness(){return _thickness;}
    const float& thickness()const{return _thickness;}

private:
    float _length;
    float _thickness;
};

#endif // COORDSYSTEMAXES_H
