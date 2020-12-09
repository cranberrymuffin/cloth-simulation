#include "Cylinder.h"
#include "Cap.h"
#include <math.h>

Cylinder::Cylinder()
{

}

void Cylinder::buildShape(int param1, int param2, int param3)
{
    m_vertices.clear();
    m_normals.clear();
    m_vertexData.clear();
    m_uv.clear();

   if(param2<3)
   {
       param2 = 3;
   }

   std::vector<Vertex> vertices;

   numYPoints = param2 +1;
   numXPoints = param1 +1;



   for(float i = 360.f ; i > 0.f  ;i-= (360.f/param2))
   {
       float angle = (float)i*PI/180.0;
       float x = 0.5*  cosf(angle);
       float z = 0.5* sinf(angle);
       float theta = atan2f(z,x);
       float u = 0;
       if(theta < 0.f)
       {
         u = -theta/(2*PI);
       }else
       {
         u = 1 - (theta/(2*PI));
       }


       Normal n(glm::normalize(glm::vec3(cosf(angle),0.0,sinf(angle))));
       for(float j=-0.5; j <= 0.5; j+=(1.0/param1))
       {
          Vertex vertex(x,j,z);
          float v = j+0.5;
          TextureCoord uv(u,v);

          m_vertices.push_back(vertex);
          m_normals.push_back(n);
          m_uv.push_back(uv);
       }
   }

   for(int i = 0 ;  i < numXPoints ; i++){
       m_vertices.push_back(m_vertices[i]);
       m_normals.push_back(m_normals[i]);
      m_uv.push_back(m_uv[i]);
   }

   buildFace(param1,  param2,  param3);

   vertices.insert(vertices.end(),m_vertices.begin(),m_vertices.end());
   m_vertices.clear();
   m_normals.clear();
   m_uv.clear();

   // UPPER CAP
   numYPoints = param2+1;
   numXPoints = param1+1 ;

   std::unique_ptr<Surface> cap = std::make_unique<Cap>();
   cap->buildSurface(param1,param2,param3,m_vertices,m_normals,m_uv);
   glm::mat4 translateUp = glm::translate(glm::vec3(0.0f,0.5f,0.0f));

   for(size_t i = 0; i < m_vertices.size();i++)
   {
      m_vertices[i] = (translateUp * glm::vec4(m_vertices[i],1)).xyz();
     // m_normals[i]  = (translateUp * glm::vec4(m_normals[i],1)).xyz();
   }

   vertices.insert(vertices.end(),m_vertices.begin(),m_vertices.end());

   buildFace(param1,  param2,  param3);

   // Lower CAP
   glm::mat4 translateDown = glm::translate(glm::vec3(0.0f,-0.5f,0.0f));
   glm::mat4 rotation = glm::rotate((float)PI,glm::vec3(1.0f,0.0f,0.0f));

   for(size_t i = 0; i < m_vertices.size();i++)
   {
      m_vertices[i] = (translateDown * rotation * translateDown* glm::vec4(m_vertices[i],1)).xyz();
      m_normals[i]  = -m_normals[i];
   }

   vertices.insert(vertices.end(),m_vertices.begin(),m_vertices.end());
   buildFace(param1,  param2,  param3);

   buildVAO();
   m_vertices.clear();
   m_vertices.insert(m_vertices.end(),std::make_move_iterator(vertices.begin()),
                     std::make_move_iterator(vertices.end()));

}

//glm::vec4 Cylinder::getNormalAtHit(glm::vec4 point)
//{
//    if (fabs(point.y + 0.5f) < SIGMA)
//    {
//        return glm::vec4(0.f, -1.f, 0.f,0.f);
//    }
//    if (fabs(point.y - 0.5f) < SIGMA)
//    {
//         return glm::vec4(0.f, 1.f, 0.f,0.f);
//    }
//    return glm::vec4(2.f*point.x, 0.f, 2.f*point.z,0.f);
//}

//glm::vec2 Cylinder::getTextureAtHit(glm::vec4 point)
//{
//    if (fabs(point.y + 0.5f) < SIGMA || fabs(point.x - 0.5f) < SIGMA)
//    {
//        //down & up
//        return glm::vec2( point.x+ 0.5,point.z+ 0.5);
//    }
//    float perimeter = 2.0 * 3.141516 *0.5;
//    float arcLength = atan2(point.z,point.x) * 0.5;
//    float u =  arcLength / perimeter;
//    float v = point.y+0.5;
//    return glm::vec2(u,v);
//}

