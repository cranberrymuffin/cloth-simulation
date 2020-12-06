#include "Cloth.h"
#include "gl/datatype/VAO.h"
#include "gl/datatype/VBO.h"
#include "gl/datatype/VBOAttribMarker.h"
#include "gl/shaders/ShaderAttribLocations.h"
#include "gl/GLDebug.h"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

using namespace CS123::GL;

Cloth::Cloth(float resolution, int particleWidth, int particleHeight)
{
    m_resolution = resolution,
    L_structural = (4.f/(resolution - 1.f)),
    L_shear = (sqrt(2.f) * 4.f/(resolution - 1.f)),
    L_flexion = 2 * L_structural;

    particles.clear();
    particles.reserve(resolution * resolution);
    numXPoints = resolution;
    numYPoints = resolution;

    for(int j = 0; j < m_resolution; j++) {
        for(int i = 0; i< m_resolution; i++) {
            float x = -2.f + 4.f*j/(resolution - 1.f);
            float y = -2.f + 4.f*i/(resolution - 1.f);

            particles[getIndex(i, j)] = ClothParticle(glm::vec3(x,y,0), particleMass, glm::vec2(x/(particleWidth-1), y/(particleHeight-1)));
        }
    }

    computeNormals();

    particles[getIndex(m_resolution - 1,0)].isStatic= true;
    particles[getIndex(m_resolution - 1, m_resolution - 1)].isStatic= true;

    buildShape(0, 0, 0);
}

void Cloth::buildShape(int param1, int param2, int param3)
{
    buildFace( param1,  param2,  param3);
    buildVAO();
}

void Cloth::buildFace(int param1,int param2, int param3)
{
    m_vertexData.clear();

    for(int i = 0 ; i < m_resolution - 1; i++)
    {
        for(int j = 0 ; j < m_resolution - 1; j++)
        {
           int thirdPoint = getIndex(i, j);
           int secondPoint = getIndex(i, j + 1);
           int firstPoint = getIndex(i+1, j + 1);
           int fourthPoint = getIndex(i+1, j);

           // here I am creating the triangles and sending them as vertex data
           Vertex v1 = particles[firstPoint].m_pos;
           Vertex v2 = particles[secondPoint].m_pos;
           Vertex v3 = particles[thirdPoint].m_pos;
           Vertex v4 = particles[fourthPoint].m_pos;
           Vertex n1 = particles[firstPoint ].m_normal;
           Vertex n2 = particles[secondPoint].m_normal;
           Vertex n3 = particles[thirdPoint].m_normal;
           Vertex n4 = particles[fourthPoint].m_normal;

           //getTextCoordinates(); ??

           TextureCoord t1 = particles[firstPoint].m_uv;
           TextureCoord t2 = particles[secondPoint].m_uv;
           TextureCoord t3 = particles[thirdPoint].m_uv;
           TextureCoord t4 = particles[fourthPoint].m_uv;

           m_vertexData.push_back(v1.x);
           m_vertexData.push_back(v1.y);
           m_vertexData.push_back(v1.z);
           m_vertexData.push_back(n1.x);
           m_vertexData.push_back(n1.y);
           m_vertexData.push_back(n1.z);
           /*m_vertexData.push_back(t1.x);
           m_vertexData.push_back(t1.y)*/;

           m_vertexData.push_back(v2.x);
           m_vertexData.push_back(v2.y);
           m_vertexData.push_back(v2.z);
           m_vertexData.push_back(n2.x);
           m_vertexData.push_back(n2.y);
           m_vertexData.push_back(n2.z);
//           m_vertexData.push_back(t2.x);
//           m_vertexData.push_back(t2.y);

           m_vertexData.push_back(v3.x);
           m_vertexData.push_back(v3.y);
           m_vertexData.push_back(v3.z);
           m_vertexData.push_back(n3.x);
          m_vertexData.push_back(n3.y);
          m_vertexData.push_back(n3.z);
//           m_vertexData.push_back(t3.x);
//           m_vertexData.push_back(t3.y);

           m_vertexData.push_back(v1.x);
           m_vertexData.push_back(v1.y);
           m_vertexData.push_back(v1.z);
           m_vertexData.push_back(n1.x);
           m_vertexData.push_back(n1.y);
           m_vertexData.push_back(n1.z);
//           m_vertexData.push_back(t1.x);
//           m_vertexData.push_back(t1.y);

           m_vertexData.push_back(v3.x);
           m_vertexData.push_back(v3.y);
           m_vertexData.push_back(v3.z);
           m_vertexData.push_back(n3.x);
           m_vertexData.push_back(n3.y);
           m_vertexData.push_back(n3.z);
//           m_vertexData.push_back(t3.x);
//           m_vertexData.push_back(t3.y);

           m_vertexData.push_back(v4.x);
           m_vertexData.push_back(v4.y);
           m_vertexData.push_back(v4.z);
           m_vertexData.push_back(n4.x);
           m_vertexData.push_back(n4.y);
          m_vertexData.push_back(n4.z);
//           m_vertexData.push_back(t4.x);
//           m_vertexData.push_back(t4.y);

        }
    }
}

int Cloth::getIndex(int i, int j) {
    return i * m_resolution + j;
}

bool Cloth::isValid(int i, int j) {
    return (i < m_resolution && i >= 0) &&(j < m_resolution && j >= 0);
}

glm::vec3 Cloth::getSpringForce(glm::vec3 p, glm::vec3 q, float K, float L_0) {
    float x = p.x - q.x;
    float y = p.y - q.y;
    float z = p.z - q.z;

    float length = sqrt((x * x) + (y * y) + (z * z));

    return (K * (L_0 - length)) * glm::normalize(p - q);
}

void Cloth::computeNormals() {
    std::vector<float> dx = std::vector<float>({1.f, 1.f, 0.f, -1.f, -1.f, 0.f});
    std::vector<float> dy = std::vector<float>({0.f, 1.f, 1.f, 0.f, -1.f, -1.f});
    glm::vec3 e1;
    glm::vec3 e2;

    for (int i = 0; i < m_resolution; ++i )
        for (int j = 0; j < m_resolution; ++j ) {
            glm::vec3 p0 = particles[getIndex(i, j)].m_pos;
            std::vector<glm::vec3>norms;
            norms.clear();
            int numNorms = 0;
            for (int t = 0; t < 6; ++t ) {
                int i1 = i + dy[t];
                int j1 = j + dx[t];
                int i2 = i + dy[(t + 1) % 6];
                int j2 = j + dx[(t + 1) % 6];
                if ( i1 >= 0 && i1 < m_resolution && j1 >= 0 && j1 < m_resolution &&
                     i2 >= 0 && i2 < m_resolution && j2 >= 0 && j2 < m_resolution ) {
                    e1 = particles[getIndex(i1, j1)].m_pos - p0;
                    e2 = particles[getIndex(i2, j2)].m_pos - p0;
                    norms.push_back(glm::normalize(glm::cross(e1, e2)));
                    numNorms++;
                }
            }
            e1 = glm::vec3(0.f,0.f,0.f);
            for (int t = 0; t < numNorms; ++t) {
                e1 = e1 + norms[t];
            }
            if(fabs(glm::length(e1)) < 0.0001)
            {
                e1 = glm::normalize(glm::vec3(0.f,1.f,1.f));
            }
            else
            {
              e1 = glm::normalize(e1);
            }


            particles[getIndex(i, j)].m_normal = e1;
        }
}

void Cloth::update(float stepSize)
{
    for ( int i = 0; i < m_resolution; ++i )
    {
        for ( int j = 0; j < m_resolution; ++j )
        {
            int index = getIndex(i, j);

            ClothParticle particle = particles[index];
            glm::vec3 v = particle.m_velocity;
            glm::vec3 x = particle.m_pos;
            glm::vec3 n = particle.m_normal;

            glm::vec3 f_spring = glm::vec3(0.f,0.f,0.f);
            /** STRUCTURAL SPRING FORCES **/
            if(isValid(i, j+1)) {
                f_spring = (f_spring + getSpringForce(x, particles[getIndex(i, j+1)].m_pos, K_structural, L_structural));
            }
            if(isValid(i, j-1)) {
                f_spring = (f_spring + getSpringForce(x, particles[getIndex(i, j-1)].m_pos, K_structural, L_structural));
            }
            if(isValid(i+1, j)) {
                f_spring = (f_spring + getSpringForce(x, particles[getIndex(i+1, j)].m_pos, K_structural, L_structural));
            }
            if(isValid(i-1, j)) {
                f_spring = (f_spring + getSpringForce(x, particles[getIndex(i-1, j)].m_pos, K_structural, L_structural));
            }

            /** SHEAR SPRING FORCES **/
            if(isValid(i+1, j+1)) {
                f_spring = (f_spring + getSpringForce(x, particles[getIndex(i+1, j+1)].m_pos, K_shear, L_shear));
            }
            if(isValid(i+1, j-1)) {
                f_spring = (f_spring + getSpringForce(x, particles[getIndex(i+1, j-1)].m_pos, K_shear, L_shear));
            }
            if(isValid(i-1, j-1)) {
                f_spring = (f_spring + getSpringForce(x, particles[getIndex(i-1, j-1)].m_pos, K_shear, L_shear));
            }
            if(isValid(i-1, j+1)) {
                f_spring = (f_spring + getSpringForce(x, particles[getIndex(i-1, j+1)].m_pos, K_shear, L_shear));
            }

            /** FLEXION SPRING FORCES **/
            if(isValid(i, j+2)) {
                f_spring = (f_spring + getSpringForce(x, particles[getIndex(i, j+2)].m_pos, K_flexion, L_flexion));
            }
            if(isValid(i, j-2)) {
                f_spring = (f_spring + getSpringForce(x, particles[getIndex(i, j-2)].m_pos, K_flexion, L_flexion));
            }
            if(isValid(i+2, j)) {
                f_spring = (f_spring + getSpringForce(x, particles[getIndex(i+2, j)].m_pos, K_flexion, L_flexion));
            }
            if(isValid(i-2, j)) {
                f_spring = (f_spring + getSpringForce(x, particles[getIndex(i-2, j)].m_pos, K_flexion, L_flexion));
            }

            glm::vec3 f_gravity = glm::vec3(0.f, -9.8f * particles[index].m_mass, 0.f);
            glm::vec3 f_damping = particles[index].m_velocity * -1.f * Cd;
            glm::vec3 f_viscous = Cv * glm::dot(particles[index].m_normal, Ufluid - particles[index].m_velocity) * particles[index].m_normal;

            particles[index].m_force = f_gravity + f_damping + f_viscous + f_spring;
            particles[index].m_velocity = particles[index].m_velocity + (stepSize * (particles[index].m_force/particles[index].m_mass));
            glm::vec3 newPos = particles[index].m_pos + (particles[index].m_velocity * stepSize);
            if(!particles[index].isStatic) {
                particles[index].m_pos = newPos;
            }
        }
    }

    computeNormals();
    buildFace(0,0,0);
}

void Cloth::draw()
{
//     glBindVertexArray(m_vaohandle);
//     glDrawArrays(GL_TRIANGLES, 0, numVertices);
//     glBindVertexArray(0);

    updateBuffer();

}

void Cloth::buildVAO()
{
    const int numFloatsPerVertex = 6;
    const int numVertices = m_vertexData.size() / numFloatsPerVertex;

    std::vector<VBOAttribMarker> markers;
    markers.push_back(VBOAttribMarker(ShaderAttrib::POSITION, 3, 0));
    markers.push_back(VBOAttribMarker(ShaderAttrib::NORMAL, 3, 3*sizeof(float)));

    m_VBO = std::make_unique<VBO>(m_vertexData.data(), m_vertexData.size(), markers, VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES, GL_DYNAMIC_DRAW);
    m_VAO = std::make_unique<VAO>(*m_VBO.get(), numVertices);
}

void Cloth::updateBuffer()
{

    if (m_VAO) {
        m_VAO->bind();

       checkError();
       m_VBO->updateBuffer(m_vertexData.data(), m_vertexData.size());
       m_VAO->draw();

       checkError();

        m_VAO->unbind();

       checkError();

    }
}
