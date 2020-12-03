#include "cubeshape.h"
#include "Plane.h"
CubeShape::CubeShape( ):numPoints(0)
{

}

void CubeShape::buildShape(int param1,int param2, int param3)
{

  m_vertices.clear();
  m_normals.clear();
  m_vertexData.clear();
  m_uv.clear();



  std::vector<Vertex> vertices;


  numXPoints = param1+1;
  numYPoints = param1+1;

  //frontface
  //   V2---V4
  //   |   / |
  //   |  /  |
  //   | /   |
  //   V1---V3


  std::unique_ptr<Surface> plane = std::make_unique<Plane>();
  plane->buildSurface(param1, param2,param3,m_vertices,m_normals,m_uv);


    glm::mat4 translateFront = glm::translate(glm::vec3(0,0,0.5));
    for(size_t i = 0; i < m_vertices.size();i++)
    {
       m_vertices[i] = (translateFront * glm::vec4(m_vertices[i],1)).xyz();
       m_normals[i] = (translateFront * glm::vec4(m_normals[i],1)).xyz();
    }

    vertices.insert(vertices.end(),m_vertices.begin(),m_vertices.end());

    buildFace(param1,  param2,  param3);


    //upface
    //   V2---V4
    //   |   / |
    //   |  /  |
    //   | /   |
    //   V1---V3


    glm::mat4 translateCenter = glm::translate(glm::vec3(0,0,-0.5));
    glm::mat4 rotation = glm::rotate((float)-PI/2,glm::vec3(1.0f,0.0f,0.0f));
    glm::mat4 translateUp = glm::translate(glm::vec3(0,0.5,0));
    for(size_t i = 0; i < m_vertices.size();i++)
    {
       m_vertices[i] = (translateUp * rotation * translateCenter * glm::vec4(m_vertices[i],1)).xyz();
       m_normals[i] = (translateUp * rotation * translateCenter * glm::vec4(m_normals[i],1)).xyz();
    }

   vertices.insert(vertices.end(),m_vertices.begin(),m_vertices.end());

  buildFace(param1,  param2,  param3);


  //  //backface
  //  //   V2---V4
  //  //   |   / |
  //  //   |  /  |
  //  //   | /   |
  //  //   V1---V3
  translateCenter = glm::translate(glm::vec3(0,-0.5,0));
  rotation = glm::rotate((float)-PI/2,glm::vec3(1.0f,0.0f,0.0f));
  glm::mat4 translateBack = glm::translate(glm::vec3(0,0,-0.5));
  for(size_t i = 0; i < m_vertices.size();i++)
  {
     m_vertices[i] = (translateBack * rotation * translateCenter * glm::vec4(m_vertices[i],1)).xyz();
     m_normals[i] = (translateBack * rotation * translateCenter * glm::vec4(m_normals[i],1)).xyz();
  }

  vertices.insert(vertices.end(),m_vertices.begin(),m_vertices.end());

  buildFace(param1,  param2,  param3);



//  m_vertices.clear();
//  // downface
//  //   V2---V4
//  //   |   / |
//  //   |  /  |
//  //   | /   |
//  //   V1---V3

  translateCenter = glm::translate(glm::vec3(0,0,0.5));
  rotation = glm::rotate((float)-PI/2,glm::vec3(1.0f,0.0f,0.0f));
  glm::mat4 translateDown = glm::translate(glm::vec3(0,-0.5,0));
  for(size_t i = 0; i < m_vertices.size();i++)
  {
     m_vertices[i] = (translateDown * rotation * translateCenter * glm::vec4(m_vertices[i],1)).xyz();
     m_normals[i] = (translateDown * rotation * translateCenter * glm::vec4(m_normals[i],1)).xyz();
  }

  vertices.insert(vertices.end(),m_vertices.begin(),m_vertices.end());

  buildFace(param1,  param2,  param3);


//  // Leftface
//  //   V2---V4
//  //   |   / |
//  //   |  /  |
//  //   | /   |
//  //   V1---V3


  translateCenter = glm::translate(glm::vec3(0,0.5,0.0));
  rotation = glm::rotate((float)-PI/2,glm::vec3(1.0f,0.0f,0.0f));
  glm::mat4 rotation2 = glm::rotate((float)-PI/2,glm::vec3(0.0f,1.0f,0.0f));
  glm::mat4 translateLeft = glm::translate(glm::vec3(-0.5,0,0));
  for(size_t i = 0; i < m_vertices.size();i++)
  {
     m_vertices[i] = (translateLeft * rotation2 * rotation * translateCenter * glm::vec4(m_vertices[i],1)).xyz();
     m_normals[i] = (translateLeft * rotation2 * rotation * translateCenter * glm::vec4(m_normals[i],1)).xyz();
  }

   vertices.insert(vertices.end(),m_vertices.begin(),m_vertices.end());

  buildFace(param1,  param2,  param3);


//  m_vertices.clear();
//  // Rightface
//  //   V2---V4
//  //   |   / |
//  //   |  /  |
//  //   | /   |
//  //   V1---V3


  translateCenter = glm::translate(glm::vec3(0.5,0.0,0.0));
  rotation = glm::rotate((float)-PI,glm::vec3(0.0f,1.0f,0.0f));
  glm::mat4 translateRight = glm::translate(glm::vec3(0.5,0.0,0.0));
  for(size_t i = 0; i < m_vertices.size();i++)
  {
     m_vertices[i] = (translateRight * rotation* translateCenter * glm::vec4(m_vertices[i],1)).xyz();
     m_normals[i] = (translateRight * rotation * translateCenter * glm::vec4(m_normals[i],1)).xyz();
  }

  vertices.insert(vertices.end(),m_vertices.begin(),m_vertices.end());

  buildFace(param1,  param2,  param3);


  buildVAO();


  m_vertices.clear();
  m_vertices.insert(m_vertices.end(),std::make_move_iterator(vertices.begin()),
                    std::make_move_iterator(vertices.end()));


}

//glm::vec4 CubeShape::getNormalAtHit(glm::vec4 point)
//{
//    if (fabs(point.x + 0.5f) < SIGMA)
//    {
//        return glm::vec4(-1.f, 0.f, 0.f,0.f);
//    }
//    if (fabs(point.x - 0.5f) < SIGMA)
//    {
//       return glm::vec4(1.f, 0.f, 0.f,0.f);
//    }
//    if (fabs(point.y + 0.5f) < SIGMA)
//    {
//        return glm::vec4(0.f, -1.f, 0.f,0.f);
//    }
//    if (fabs(point.y - 0.5f) < SIGMA)
//    {
//        return glm::vec4(0.f, 1.f, 0.f,0.f);
//    }
//    if (fabs(point.z + 0.5f) < SIGMA)
//    {
//         return glm::vec4(0.f, 0.f, -1.f,0.f);
//    }
//    if (fabs(point.z - 0.5f) < SIGMA)
//    {
//       return glm::vec4(0.f, 0.f, 1.f,0.f);
//    }

//}

//glm::vec2 CubeShape::getTextureAtHit(glm::vec4 point)
//{
//    if (fabs(point.x +  0.5) < SIGMA || fabs(point.x - 0.5) < SIGMA)
//    {
//        //right & left
//        //return glm::vec4(-1.f, 0.f, 0.f,0.f);
//        return glm::vec2(point.z+ 0.5,point.y+ 0.5);

//    }
////    if (fabs(point.x - 0.5f) < SIGMA)
////    {
////        // left
////       return glm::vec4(1.f, 0.f, 0.f,0.f);
////    }
////    float a =point.y - 0.5f;
////    bool p = fabs(point.y - 0.5f)< SIGMA;
//    if (fabs(point.y + 0.5) < SIGMA )
//    {
//        //down & up
//        return glm::vec2( point.x+ 0.5,point.z+ 0.5);
//    }
//    if(fabs(point.y - 0.f) < SIGMA)
//    {
//        return glm::vec2( point.x+ 0.5,  0.5 -point.z);
//    }
////    if (fabs(point.y - 0.5f) < SIGMA)
////    {
////        //up
////        return glm::vec4(0.f, 1.f, 0.f,0.f);
////    }
//    if (fabs(point.z + 0.5) <SIGMA || fabs(point.z - 0.5) < SIGMA)
//    {
//        //front & back
//         //return glm::vec4(0.f, 0.f, -1.f,0.f);
//        return glm::vec2(point.x+ 0.5, point.y+ 0.5) ;
//    }
////    if (fabs(point.z - 0.5f) < SIGMA)
////    {
////        //back
////       return glm::vec4(0.f, 0.f, 1.f,0.f);
////    }
//}




