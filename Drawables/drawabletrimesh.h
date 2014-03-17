#ifndef DRAWABLETRIMESH_H
#define DRAWABLETRIMESH_H

#include "drawableintrfc.h"
#include "surface_mesh/Surface_mesh.h"

namespace SurfaceMesh = surface_mesh;
class DrawableTriMesh: public DrawableIntrfc
{
public:
    typedef SurfaceMesh::Surface_mesh Mesh;


public:
    DrawableTriMesh();
    virtual ~DrawableTriMesh(){}
    virtual void draw()const{};

private:
    Mesh _mesh;
};

#endif // DRAWABLETRIMESH_H
