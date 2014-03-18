#ifndef DRAWABLETRIMESH_H
#define DRAWABLETRIMESH_H

#include "drawableintrfc.h"
#include "../Utils/abstractlog.h"
#include "surface_mesh/Surface_mesh.h"

namespace SurfaceMesh = surface_mesh;
class DrawableTriMesh: public DrawableIntrfc
{
public:
    typedef SurfaceMesh::Surface_mesh Mesh;


public:
    DrawableTriMesh();
    virtual ~DrawableTriMesh(){}
    virtual void draw()const{}

    Mesh& mesh(){return _mesh;}
    const Mesh& mesh()const{return _mesh;}


private:
    Mesh _mesh;
};

namespace IO{
    void importDrawableTriMesh(DrawableTriMesh& dmesh, const std::string& filename, AbstractLog* log = nullptr);
}


#endif // DRAWABLETRIMESH_H
