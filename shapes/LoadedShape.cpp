#include "LoadedShape.h"
#include "gl/GLDebug.h"

using namespace CS123::GL;
LoadedShape::LoadedShape(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals,
    std::vector<glm::vec2>& textCoords)
{

    m_vertices = vertices;
    m_normals = normals;
    m_textCoords = textCoords;

    bbv_vertices = {
        glm::vec3(-0.5, 0.0, 0.0),
        glm::vec3(0.5, 0.0, 0.5),
        glm::vec3(0.0, 0.5, 0.0),
    };

    indexes = {
        0, 1, 2, 3,
        4, 5, 6, 7,
        0, 4, 1, 5, 2, 6, 3, 7
    };

    //       glGenVertexArrays(1, &vao_BoundingBox);
    //       glBindVertexArray(vao_BoundingBox);

    //       glGenBuffers(1, &vbo_BoundingBox);
    //       glBindBuffer(GL_ARRAY_BUFFER, vbo_BoundingBox);
    //       glBufferData(GL_ARRAY_BUFFER, bbv_vertices.size()*sizeof(glm::vec3), &bbv_vertices[0], GL_STATIC_DRAW);
    //       glEnableVertexAttribArray(0);
    //       glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(glm::vec3), (GLvoid*)0);
    //       glBindBuffer(GL_ARRAY_BUFFER,0);

    //        glGenBuffers(1, &indexes_BoundingBox);
    //        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes_BoundingBox);
    //        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size()*sizeof (int), &indexes[0], GL_STATIC_DRAW);

    //      glBindVertexArray(0);
    buildVAO();
}

LoadedShape::LoadedShape(std::vector<float>& vtf, std::vector<glm::vec3>& n, std::vector<glm::vec2>& t)
{
    m_vertf = vtf;

    glGenVertexArrays(1, &vao);
    checkError();
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    //vbos.push_back(vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertf.size(),
        &m_vertf[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void LoadedShape::buildShape(int param1, int param2, int param3)
{
}

LoadedShape::~LoadedShape()
{
    //    for(GLuint vbo:vbos)
    //    {
    //      glDeleteBuffers(1,&vbo);
    //    }

    //    glDeleteVertexArrays(1,&vao);
}

void LoadedShape::draw()
{
    //    glBindVertexArray(vao_BoundingBox);
    //    checkError();
    //    glDrawArrays(GL_TRIANGLES,0,bbv_vertices.size());
    //    checkError();
    //    glBindVertexArray(0);
    int sizeVertices = bbv_vertices.size() / sizeof(glm::vec3);
    //int sizeVertices = m_vertices.size() / sizeof(float);

    glBindVertexArray(vao);

    checkError();
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
    checkError();
    // glBindVertexArray(0);

    //        glBindVertexArray(vao_BoundingBox);
    //        glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, 0);
    ////        CS123::GL::checkError();
    ////        glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (GLvoid*)(4*sizeof(GLushort)));
    ////        CS123::GL::checkError();
    ////        glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, (GLvoid*)(8*sizeof(GLushort)));
    ////        CS123::GL::checkError();
    //     //   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //        glBindVertexArray(0);
    //        CS123::GL::checkError();

    //        glDisableVertexAttribArray(0);
    //        CS123::GL::checkError();
    //        glBindBuffer(GL_ARRAY_BUFFER, 0);
    //        CS123::GL::checkError();
}

void LoadedShape::buildVAO()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //    if(!m_normals.empty())
    //    {
    //        GLuint vbon;
    //        glGenBuffers(1, &vbon);
    //        vbos.push_back(vbon);
    //        glBindBuffer(GL_ARRAY_BUFFER, vbon);
    //        glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(glm::vec3),
    //                &m_normals[0], GL_STATIC_DRAW);
    //        glEnableVertexAttribArray(1);
    //        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3),0);
    //        //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //    }

    //    if(!m_textCoords.empty())
    //    {
    //        GLuint vbot;
    //        glGenBuffers(1, &vbot);
    //        vbos.push_back(vbot);
    //        glBindBuffer(GL_ARRAY_BUFFER, vbot);
    //        glBufferData(GL_ARRAY_BUFFER, m_textCoords.size() * sizeof(glm::vec2),
    //                &m_textCoords[0], GL_STATIC_DRAW);
    //        glEnableVertexAttribArray(2);
    //        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2),0);
    //        //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //    }

    checkError();
    //     glGenBuffers(1, &indexes_BoundingBox);
    //     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes_BoundingBox);
    //     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
}
