#include "drawabletrimesh.h"
#include "surface_mesh/IO.h"
#include "QFileInfo"

DrawableTriMesh::DrawableTriMesh()
{
}


namespace IO{

    void importDrawableTriMesh(DrawableTriMesh& dmesh, const std::string& filename, AbstractLog* log){
        SECURE_LOG(log,"Importing a DrawableTriMesh...");
        const QFileInfo fileInfo(QString::fromStdString(filename));
        if(!fileInfo.exists())
            throw std::runtime_error("File does not exist");

        const QString extension(fileInfo.suffix());
        if(extension.compare("obj",Qt::CaseInsensitive)==0){
            SECURE_LOG_VAL(log,"Mesh type","Obj");
            SurfaceMesh::read_obj(dmesh.mesh(),filename);
        }else if(extension.compare("off",Qt::CaseInsensitive)==0){
            SECURE_LOG_VAL(log,"Mesh type","Off");
            SurfaceMesh::read_off(dmesh.mesh(),filename);
        }else if(extension.compare("stl",Qt::CaseInsensitive)==0){
            SECURE_LOG_VAL(log,"Mesh type","Stl");
            SurfaceMesh::read_stl(dmesh.mesh(),filename);
        }
        DrawableTriMesh::Mesh& mesh(dmesh.mesh());
        if(!mesh.is_triangle_mesh()){
            mesh.clear();
            throw std::runtime_error("Input mesh is not a triangle mesh");
        }
        SECURE_LOG_VAL(log,"# of vertices", mesh.n_vertices());
        SECURE_LOG_VAL(log,"# of faces",    mesh.n_faces());
        SECURE_LOG_VAL(log,"# of edges",    mesh.n_edges());
        SECURE_LOG_VAL(log,"# of halfedges",mesh.n_halfedges());
    }

}
