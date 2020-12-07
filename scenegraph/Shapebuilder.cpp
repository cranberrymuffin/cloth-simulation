#include "Shapebuilder.h"
#include "shapes/Cone.h"
#include "shapes/cubeshape.h"
#include "shapes/Cylinder.h"
#include "shapes/Sphere.h"


ShapeBuilder::~ShapeBuilder()
{
    std::map<std::string,Shape*>::iterator it;

    for ( it = m_shapes.begin(); it != m_shapes.end(); it++ ){
      delete it->second;
    }
}

Shape* ShapeBuilder::LoadShape(PrimitiveType type,int param1, int param2)
{
    std::string shapeName = std::to_string((int)type)+std::to_string(param1)+":"+std::to_string(param2);
    Shape* shape = nullptr;
    if( m_shapes.find(shapeName) == m_shapes.end()  )
    {
        switch(type)
        {
         case PrimitiveType::PRIMITIVE_CONE:
            shape = new Cone();
            shape->buildShape(param1,param2,0);

            break;
         case PrimitiveType::PRIMITIVE_CUBE:
            shape = new CubeShape();
            shape->buildShape(param1,param2,0);

            break;
         case PrimitiveType::PRIMITIVE_CYLINDER:
            shape = new Cylinder();
            shape->buildShape(param1,param2,0);

           break;
         case PrimitiveType::PRIMITIVE_SPHERE:
            shape = new Sphere();
            shape->buildShape(param1,param2,0);
            break;
          default:
            return nullptr;
        }

        m_shapes[shapeName] =shape;

    }

    return m_shapes[shapeName];


}

void ShapeBuilder::setMeshLoadedShape(std::string &filename, Shape *shape)
{
     if( m_shapes.find(filename) == m_shapes.end()  )
     {
            m_shapes[filename] =shape;
     }
}

Shape *ShapeBuilder::getMeshLoadedShape(std::string &filename)
{
    if( m_shapes.find(filename) != m_shapes.end()  )
    {
        return   m_shapes[filename] ;
    }
    return nullptr;
}

