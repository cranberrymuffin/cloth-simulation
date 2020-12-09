#include "Sphere.h"

Sphere::Sphere()
{

}

void Sphere::buildShape(int param1, int param2, int param3)
{
    m_vertices.clear();
    m_normals.clear();
    m_vertexData.clear();
    m_uv.clear();

    if(param1<2)
    {
        param1 = 2;
    }

    if(param2<3)
    {
        param2 = 3;
    }

    numYPoints = param2 +1;
    numXPoints = param1 +1;

   float radius =0.5;
   for(float phi = 360.f ; phi > 0.f  ;phi-= (360.f/param2)){
       float tu = 0.f;
       if(phi < 0)
       {
        tu = -phi/(2.f*PI);
       }else
       {
        tu = 1 - (phi/(2.f*PI));
       }



       for(float theta = 180.f ; theta >=0.f  ;theta-= (180.f/param1))
       {

               float x = radius * sinf(theta*PI/180.f) * cosf(phi*PI/180.f);
               float z = radius * sinf(theta*PI/180.f) * sinf(phi*PI/180.f);
               float y = radius *cosf(theta*PI/180.f);

               float tv =  asinf(y/radius);
               tv = (tv/PI) + (1.0/2.0);
               if(abs(tv ) < 0.0005 || abs(tv - 1) < 0.0005)
               {
                   tu = 0.5;
               }


               Vertex v(x,y,z);
               Normal n(x,y,z);
               TextureCoord t(tu,tv);

               m_vertices.push_back(v);
               m_normals.push_back(n);
               m_uv.push_back(t);
       }
   }

   for(int i = 0 ;  i < numXPoints ; i++){

       m_vertices.push_back(m_vertices[i]);
       m_normals.push_back(m_normals[i]);
   }


   this->buildFace(param1,  param2,  param3);
   buildVAO();
}
