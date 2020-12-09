#ifndef LOADEDSHAPE_H
#define LOADEDSHAPE_H
#include "shapes/Shape.h"

class LoadedShape : public Shape {
public:
    LoadedShape(std::vector<glm::vec3>&, std::vector<glm::vec3>&,
        std::vector<glm::vec2>&);

    LoadedShape(std::vector<float>&, std::vector<glm::vec3>&,
        std::vector<glm::vec2>&);

    void buildShape(int param1, int param2, int param3);
    ~LoadedShape();

protected:
    void buildVAO();
    void draw();
    std::string m_filename;
    std::vector<glm::vec3> m_vertices;
    std::vector<float> m_vertf;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::vec2> m_textCoords;
    std::vector<int> indexes;
    std::vector<glm::vec3> bbv_vertices;

    GLuint vao;
    GLuint vbo;
    std::vector<GLuint> vbos;

    GLuint vao_BoundingBox;
    GLuint vbo_BoundingBox;
    GLuint indexes_BoundingBox;

    //GLuint vbo;
};

#endif // LOADEDSHAPE_H
