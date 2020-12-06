#include "Shape.h"
#include "gl/datatype/VAO.h"
#include "gl/datatype/VBO.h"
#include "gl/datatype/VBOAttribMarker.h"
#include "gl/shaders/ShaderAttribLocations.h"
#include "common/common.h"
#include "gl/GLDebug.h"
using namespace CS123::GL;

Shape::Shape() :
    m_VAO(nullptr)
{

}



Shape::~Shape()
{
}


void Shape::draw() {
    if (m_VAO) {
        m_VAO->bind();
        m_VAO->getVBO()->updateBuffer(m_vertexData.data(), m_vertexData.size()/6);
        checkError();

        m_VAO->draw();

       checkError();

        m_VAO->unbind();

       checkError();

    }
}

void Shape::buildVAO() {
    const int numFloatsPerVertex = 8;
    const int numVertices = m_vertexData.size() / numFloatsPerVertex;

    std::vector<VBOAttribMarker> markers;
    markers.push_back(VBOAttribMarker(ShaderAttrib::POSITION, 3, 0));
    markers.push_back(VBOAttribMarker(ShaderAttrib::NORMAL, 3, 3*sizeof(float)));
    markers.push_back(VBOAttribMarker(ShaderAttrib::TEXCOORD0,2, 6*sizeof(float)));

    VBO vbo = VBO(m_vertexData.data(), m_vertexData.size(), markers);
    m_VAO = std::make_unique<VAO>(vbo, numVertices);
}

void Shape::buildFace(int param1,int param2, int param3)
{
    for(int i = 0 ; i < numXPoints - 1; i++)
    {
        for(int j = 0 ; j < numYPoints - 1; j++)
        {
           int firstPoint = i + j * numXPoints;
           int secondPoint = (i + j * numXPoints) + numXPoints;
           int thirdPoint = (i + j * numXPoints) + numXPoints + 1;

           // here I am creating the triangles and sending them as vertex data
           Vertex v1 = m_vertices[firstPoint];
           Vertex v2 = m_vertices[secondPoint];
           Vertex v3 = m_vertices[thirdPoint];

           Vertex n1 = m_normals[firstPoint ];
           Vertex n2 = m_normals[secondPoint];
           Vertex n3 = m_normals[thirdPoint];

           //getTextCoordinates(); ??

           TextureCoord t1 = m_uv[firstPoint];
           TextureCoord t2 = m_uv[secondPoint];
           TextureCoord t3 = m_uv[thirdPoint];

           m_vertexData.push_back(v1.x);
           m_vertexData.push_back(v1.y);
           m_vertexData.push_back(v1.z);
           m_vertexData.push_back(n1.x);
           m_vertexData.push_back(n1.y);
           m_vertexData.push_back(n1.z);
           m_vertexData.push_back(t1.x);
           m_vertexData.push_back(t1.y);

           m_vertexData.push_back(v2.x);
           m_vertexData.push_back(v2.y);
           m_vertexData.push_back(v2.z);
           m_vertexData.push_back(n2.x);
           m_vertexData.push_back(n2.y);
           m_vertexData.push_back(n2.z);
           m_vertexData.push_back(t2.x);
           m_vertexData.push_back(t2.y);

           m_vertexData.push_back(v3.x);
           m_vertexData.push_back(v3.y);
           m_vertexData.push_back(v3.z);
           m_vertexData.push_back(n3.x);
           m_vertexData.push_back(n3.y);
           m_vertexData.push_back(n3.z);
           m_vertexData.push_back(t3.x);
           m_vertexData.push_back(t3.y);

           int fourth =(i + j * numXPoints )+1;

           Vertex v4 = m_vertices[fourth];
           Vertex n4 = m_normals[fourth];
           TextureCoord t4 = m_uv[fourth];

           m_vertexData.push_back(v1.x);
           m_vertexData.push_back(v1.y);
           m_vertexData.push_back(v1.z);
           m_vertexData.push_back(n1.x);
           m_vertexData.push_back(n1.y);
           m_vertexData.push_back(n1.z);
           m_vertexData.push_back(t1.x);
           m_vertexData.push_back(t1.y);

           m_vertexData.push_back(v3.x);
           m_vertexData.push_back(v3.y);
           m_vertexData.push_back(v3.z);
           m_vertexData.push_back(n3.x);
           m_vertexData.push_back(n3.y);
           m_vertexData.push_back(n3.z);
           m_vertexData.push_back(t3.x);
           m_vertexData.push_back(t3.y);

           m_vertexData.push_back(v4.x);
           m_vertexData.push_back(v4.y);
           m_vertexData.push_back(v4.z);
           m_vertexData.push_back(n4.x);
           m_vertexData.push_back(n4.y);
           m_vertexData.push_back(n4.z);
           m_vertexData.push_back(t4.x);
           m_vertexData.push_back(t4.y);

        }
    }
}




