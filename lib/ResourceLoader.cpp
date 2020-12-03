#include "ResourceLoader.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <iostream>
#include "scenegraph/SceneObject.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader/tiny_obj_loader.h"
#include "shapes/LoadedShape.h"
#include "scenegraph/SceneObject.h"
#include "lib/CS123SceneData.h"

std::string ResourceLoader::loadResourceFileToString(const std::string &resourcePath)
{
    QString vertFilePath = QString::fromStdString(resourcePath);
    QFile vertFile(vertFilePath);
    if (vertFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream vertStream(&vertFile);
        QString contents = vertStream.readAll();
        return contents.toStdString();
    }
    throw CS123::IOException("Could not open file: " + resourcePath);
}

void ResourceLoader::readObjFile(std::vector<SceneObject*>& sceneObjects,
                                 const std::string& filename)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;


    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str());

    if (!warn.empty()) {
      std::cout << warn << std::endl;
    }

    if (!err.empty()) {
      std::cerr << err << std::endl;
    }

    if (!ret) {
     std::cerr << "Error loaded obj file" << std::endl;
      return ;
    }





    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> textCoords;

//        std::vector<float> vertices;
//        std::vector<glm::vec3> normals;
//        std::vector<glm::vec2> textCoords;

        size_t index_offset = 0;// indent offset
        for (size_t f = 0;f<shapes[s].mesh.num_face_vertices.size ();f ++)
        {

           int fv = shapes[s].mesh.num_face_vertices[f];
            for (size_t v = 0; v < fv; v++)
            {
               tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
               glm::vec3 vertex;
               vertex.x = attrib.vertices[3*idx.vertex_index+0];
               vertex.y = attrib.vertices[3*idx.vertex_index+1];
               vertex.z = attrib.vertices[3*idx.vertex_index+2];
               vertices.push_back(vertex);
//               vertices.push_back(3*idx.vertex_index+0);
//               vertices.push_back(3*idx.vertex_index+1);
//               vertices.push_back(3*idx.vertex_index+2);

               if(!attrib.normals.empty())
               {
                   glm::vec3 normal;
                   normal.x = attrib.normals[3*idx.normal_index+0];
                   normal.y = attrib.normals[3*idx.normal_index+1];
                   normal.z = attrib.normals[3*idx.normal_index+2];
                   normals.push_back(normal);
               }
               if(!attrib.texcoords.empty())
               {
                   glm::vec2 textC;
                   textC.x = attrib.normals[3*idx.texcoord_index+0];
                   textC.y = attrib.normals[3*idx.texcoord_index+1];
                   textCoords.push_back(textC);
               }



            }


        }
        Material m;
        //shapes[s].mesh.material_ids[f];
        LoadedShape* shape = new LoadedShape(vertices,normals,textCoords);
        //LoadedShape* shape = new LoadedShape(vertices,normals,textCoords);
        SceneObject* sceneObject = new SceneObject(shape,PrimitiveType::PRIMITIVE_MESH,m);
        sceneObjects.push_back(sceneObject);

      //SceneObject* sceneobject = new SceneObject();
    }

}
