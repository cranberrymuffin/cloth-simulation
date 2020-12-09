#include "Plane.h"
#include <QtGlobal>
Plane::Plane()
{

}

void Plane::buildSurface(int param1, int param2, int param3,std::vector<Vertex>& vertices,std::vector<Normal>& normals, std::vector<TextureCoord>& uv)
{
    vertices.clear();
    normals.clear();
    uv.clear();

    glm::vec3 v1(-0.5,0.0,0.0);
    glm::vec3 v2(0.0,-0.5,0.0);
    glm::vec3 v3(0.5,0.0,0.0);


    Normal n = glm::normalize(glm::cross(v2-v1,v3-v1));

    float quadSize = 1.0f/param1;
    int scaledQuad = 100 * quadSize;

    for(float i =-0.5; i <= 0.5; i += 1.0f/param1)
    {

      float u = ((float)( (int)( (i+0.5) *(100.f))%(scaledQuad)))/scaledQuad;
      u /= 100.f;

      if(qFuzzyCompare(u,0.f) && qFuzzyCompare(i+0.5f,quadSize))
      {
          u = 1.0;
      }


      for(float j =-0.5; j <= 0.5; j += (1.0f/param1))
      {
          float v= ((float)( (int)( (j+0.5) *(100.f))%(scaledQuad)))/scaledQuad;
          v /=100.f;

          if(qFuzzyCompare(v,0.f) && qFuzzyCompare(j+0.5f,quadSize))
          {
              v = 1.0;
          }

          TextureCoord txtCoord(u,v);
          Vertex vertex(i,j,0);
          vertices.push_back(vertex);
          normals.push_back(n);
          uv.push_back(txtCoord);
      }
    }



}


