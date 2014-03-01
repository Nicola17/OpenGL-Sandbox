#include "trianglesoupimporters.h"
#include <iostream>
#include <fstream>
#include <string>

namespace IO
{

    void TriangleSoupImporters::readObj(const QString& filename, TriangleSoup& triSoup, AbstractLog* log){
        SECURE_LOG_VAL(log,"Read OBJ",filename.toStdString());
        typedef TriangleSoup::vector_type vector_type;
        std::string line;
        std::ifstream infile;
        infile.open(filename.toStdString(), std::fstream::in);
        if(!infile.is_open())
            throw std::runtime_error("Unable to open the obj file");

        std::vector<vector_type> vertices;
        std::vector<vector_type> normals;

        while(!infile.eof()){
            std::getline(infile,line);

            QString qline(QString::fromStdString(line));
            QStringList tokens = qline.split(" ");

            if(tokens.size() == 0)
                continue;
            if(tokens[0].compare("v") == 0){
                vertices.push_back(vector_type(tokens[2].toFloat()/30,tokens[3].toFloat()/30,tokens[4].toFloat()/30));
            }else if(tokens[0].compare("vn") == 0){
                normals.push_back(vector_type(tokens[2].toFloat(),tokens[3].toFloat(),tokens[4].toFloat()));
            }else if(tokens[0].compare("f") == 0){
                if(tokens.size() != 4)
                    throw std::runtime_error("Invalid obj file");
                std::vector<int> vertexIdx;
                std::vector<int> normalIdx;
                std::vector<int> textureIdx;
                for(int t = 1; t < 4; ++t){
                    QStringList subTokens = tokens[t].split("/");
                    vertexIdx.push_back(subTokens[0].toUInt());
                    //TODO
                    normalIdx.push_back(subTokens[2].toUInt());
                }
                triSoup.addTriangle(vertices[vertexIdx[0]-1],vertices[vertexIdx[1]-1],vertices[vertexIdx[2]-1]);
                //triSoup.addTriangle(vertices[vertexIdx[0]-1],vertices[vertexIdx[1]-1],vertices[vertexIdx[2]-1],
                  //                  normals[normalIdx[0]-1],normals[normalIdx[1]-1],normals[normalIdx[2]-1]);
            }

        }
        SECURE_LOG_VAL(log,"v",vertices.size());
        SECURE_LOG_VAL(log,"vn",normals.size());
        infile.close();
    }

}
