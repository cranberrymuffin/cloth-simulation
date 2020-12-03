#include "Cone.h"
#include "Cap.h"

Cone::Cone()
{

}

void Cone::buildShape(int param1, int param2, int param3)
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

    numYPoints = param2+1;
    numXPoints = param1+1 ;

    // Bottom Cap
    std::unique_ptr<Surface> cap = std::make_unique<Cap>();
    cap->buildSurface(param1,param2,param3,m_vertices,m_normals,m_uv);

    glm::mat4 translateDown = glm::translate(glm::vec3(0.0f,-0.5f,0.0f));
    glm::mat4 rotation = glm::rotate((float)PI,glm::vec3(1.0f,0.0f,0.0f));

    for(int i = 0; i < m_vertices.size();i++)
    {
       m_vertices[i] = (translateDown* rotation *glm::vec4(m_vertices[i],1)).xyz();
       m_normals[i]  = -m_normals[i];
       m_uv.push_back(TextureCoord());
    }

    vertices.insert(vertices.end(),m_vertices.begin(),m_vertices.end());

    buildFace( param1,  param2,  param3);

    m_vertices.clear();
    m_normals.clear();

    numYPoints = param2 +1;
    numXPoints = param1 +1;

    int numXPoints = param1+1 ;

    Normal prevNormal;
    for(float angle = 360.f ; angle >0.f  ;angle-= (360.f/param2))
    {
        float radius = 0.5f;
        float yPos = -0.5f;
        float stepXZ = (0.5/param1);
        float stepY = (1.0/param1);


        for(float j=0.f; j <  numXPoints ; j++)
        {
            float x = radius* cosf((float)angle*PI/180.f);
            float z = radius* sinf((float)angle*PI/180.f);
            Vertex v(x,yPos,z);
            Normal n;
            TextureCoord tx;
            if(abs(x ) < 0.0005  && abs(z ) < 0.0005)
            {
               int next_angle = angle - (360.f/param2);
               glm::vec3 v0 (0.0,0.5,0.0);
               glm::vec3 v1(0.5* cosf((float)angle*PI/180),-0.5,0.5* sinf((float)angle*PI/180.f));
               glm::vec3 v2(0.5* cosf((float)next_angle*PI/180),-0.5,0.5* sinf((float)next_angle*PI/180.f) );
               n = glm::normalize(glm::cross(v2-v1,v0-v2));
            }
            else
            {
                float xsign = getSign(x);
                float zsign = getSign(z);

                n.x = (2.0/sqrtf(5.f))  * xsign;
                n.y = 1.0/sqrtf(5.f);
                n.z = 2.0/sqrtf(5.f) *zsign;


            }

//            float xsign = getSign(x);
//            float zsign = getSign(z);

//            n.x = (2.0/sqrtf(5.0))  * xsign;
//            n.y = 1.0/sqrtf(5.0);
//            n.z = (2.0/sqrtf(5.0)) *zsign;
            //prevNormal = n;
            m_vertices.push_back(v);
            m_normals.push_back(n);
            m_uv.push_back(tx);

            radius-= stepXZ;
            yPos += stepY;
        }

    }

    for(int i = 0 ;  i < numXPoints ; i++){
        m_vertices.push_back(m_vertices[i]);
        m_normals.push_back(m_normals[i]);
        m_uv.push_back(m_uv[i]);

    }
    vertices.insert(vertices.end(),m_vertices.begin(),m_vertices.end());
    buildFace(param1,  param2,  param3);
    buildVAO();

    m_vertices.clear();
    m_vertices.insert(m_vertices.end(),std::make_move_iterator(vertices.begin()),
                      std::make_move_iterator(vertices.end()));
}

//glm::vec4 Cone::getNormalAtHit(glm::vec4 point)
//{
//    if (fabs(point.y + 0.5) < SIGMA)
//    {
//       return glm::vec4(0.f, -1.f, 0.f,0.f);
//    }
//    else
//    {
//       float d = sqrtf(5.f*(point.x*point.x)+5.f*(point.z*point.z));
//       return glm::vec4((2.f*point.x)/d, sqrt(0.2f), (2.f*point.z)/d,0.f);
//    }
//}

//glm::vec2 Cone::getTextureAtHit(glm::vec4 point)
//{
//    if (fabs(point.y + 0.5) < SIGMA)
//    {
//        //down
//        return glm::vec2( point.x+ 0.5,point.z+ 0.5);
//    }
//    float perimeter = 2.0 * 3.141516 *0.5;
//    float arcLength = atan2(point.z,point.x) * 0.5;
//    float u =  arcLength / perimeter;
//    float v = point.y+0.5;
//    return glm::vec2(u,v);
//}


float Cone::getSign(float n)
{

    if(abs(n ) < 0.0005)
    {
        return 0.f;
    }

    return n > 0.0 ? 1.f:-1.f;
}
