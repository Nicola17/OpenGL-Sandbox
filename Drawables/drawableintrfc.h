#ifndef DRAWABLEINTRFC_H
#define DRAWABLEINTRFC_H

class DrawableIntrfc{
public:
    virtual ~DrawableIntrfc(){}
    virtual void draw()const=0;
};

#endif // DRAWABLEINTRFC_H
