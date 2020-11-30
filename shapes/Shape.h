#ifndef SHAPE_H
#define SHAPE_H

/** imports the OpenGL math library https://glm.g-truc.net/0.9.2/api/a00001.html */
#include <glm/glm.hpp>
#include "GL/glew.h"

#include<memory>
#include <vector>
#include "../common/common.h"



/**
 *
 * inserts a glm::vec3 into a vector of floats
 * this will come in handy if you want to take advantage of vectors to build your shape
 * make sure to call reserve beforehand to speed this up
 */
inline void insertVec3(std::vector<float> &data, glm::vec3 v){
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}

namespace CS123 { namespace GL {
class VAO;
}}

class Shape
{
public:
    Shape();

    virtual ~Shape();
    void draw();
    virtual void buildFace(int param1,int param2, int param3);
    virtual void buildShape(int param1,int param2, int param3) = 0;

    virtual glm::vec4 getNormalAtHit(glm::vec4 p){return glm::vec4();};

    virtual glm::vec2 getTextureAtHit(glm::vec4 p){return glm::vec2();};

    const std::vector<Vertex>& getVertices(){return m_vertices;};

    void getBoungdingBox(glm::vec3& min,glm::vec3& max);

protected:
    /** builds the VAO, pretty much the same as from lab 1 */
    void buildVAO();



    std::vector<GLfloat> m_vertexData;
    std::unique_ptr<CS123::GL::VAO> m_VAO;

    std::vector<Vertex> m_vertices;
    std::vector<Normal> m_normals;
    std::vector<TextureCoord> m_uv;







};

#endif // SHAPE_H
