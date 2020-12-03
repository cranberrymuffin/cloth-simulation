#include "Cap.h"

Cap::Cap()
{

}
/**
 * @brief Cap::buildSurface builds procedurally a Cap for geometric figures
 * @param param1
 * @param param2
 * @param param3
 * @return returns vertices of a face up Cap laying on the XZ plane
 */
void Cap::buildSurface(int param1, int param2, int param3,std::vector<Vertex>& m_vertices, std::vector<Normal>& m_normals, std::vector<TextureCoord>& uv)
{

    float radius = 0.5;
    float angle = 360/param2;
    glm::vec3 v1(0.0,0.0,0.0);
    glm::vec3 v2(radius* cosf((float)angle*PI/180),0.0,radius* sinf((float)angle*PI/180));
    glm::vec3 v3(radius* cosf((float)2*angle*PI/180),0.0,radius* sinf((float)2*angle*PI/180));

    //Normal n(glm::normalize(glm::cross(v2-v1,v3-v2)));
    Normal n(glm::normalize(glm::vec3(0.0,1.0,0.0)));


    // FACE UP CAP

    int numXPoints = param1+1 ;
    for(float i = 360.f ; i >0.f  ;i-= (360.f/param2))
    {
        radius = 0.5f;
        float step = (0.5f/param1);
        for(float j=0.f; j <  numXPoints ; j++)
        {
            float x = radius* cosf((float)i*PI/180.f);
            float z = radius* sinf((float)i*PI/180.f);
            Vertex v(x,0.f,z);
            m_vertices.push_back(v);
            m_normals.push_back(n);
            radius-= step;
        }

    }

    for(int i = 0 ;  i < numXPoints ; i++){

        m_vertices.push_back(m_vertices[i]);
        m_normals.push_back(m_normals[i]);
    }

}
