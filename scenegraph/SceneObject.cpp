#include "SceneObject.h"


#include <glm/gtc/type_ptr.hpp>
#include "shapes/LoadedShape.h"


SceneObject::SceneObject():m_Shape(nullptr),m_type(PrimitiveType::PRIMITIVE_CUBE),
m_Material(),m_parent(nullptr)
{

}

SceneObject::SceneObject(Shape* shape, PrimitiveType type,Material& material):m_Shape(shape),m_type(type),
    m_Material(this,material),m_parent(nullptr)
{

}

SceneObject::SceneObject(SceneObject & other):m_Shape(other.m_Shape),m_type(other.m_type),m_parent(other.m_parent),
    m_Material(other.m_Material)
{
  setModelMatrix(other.getLocalMatrix());
  setWorldMatrix(other.getToWorldMatrix());


  for(size_t i=0;i<other.children.size();i++)
  {
      SceneObject* sceneObject = new  SceneObject(*other.children[i]);
      this->children.push_back(sceneObject);
  }
}

SceneObject::~SceneObject()
{


}

void SceneObject::setPosition(Transformation position)
{

}

void SceneObject::setOrientation(Transformation orientation)
{

}

void SceneObject::setScale(Transformation scale)
{

}

void SceneObject::setMaterial(Material material)
{
    m_Material.setMaterial(material);
}

void SceneObject::setPrimitiveType(PrimitiveType primitiveType)
{
    m_type = primitiveType;
}

Transformation &SceneObject::getPosition() const
{

}

Transformation &SceneObject::getOrientation() const
{

}

Transformation &SceneObject::getScale() const
{

}

Material& SceneObject::getMaterial()
{
    return m_Material.getMaterial();
}

PrimitiveType &SceneObject::getPrimitiveType()
{
    return m_type;
}

void SceneObject::binTexture()
{
    //m_Material.getTexture().bind();
}

void SceneObject::unBinTexture()
{
    //m_Material.getTexture().unbind();
}

void SceneObject::setParent(Transformation *&parent)
{
  m_parent = parent;
}

Transformation &SceneObject::getParent()
{
  return *m_parent;
}

void SceneObject::addChild(SceneObject* &child)
{
  children.push_back(child);
}

std::vector<SceneObject*> &SceneObject::getChildren()
{
  return children;
}

void SceneObject::setModelMatrix(const glm::mat4x4 &matrix)
{
    m_localTransformation.matrix = matrix;
}

void SceneObject::setWorldMatrix(const glm::mat4x4 &matrix)
{
    m_parenTransformation.matrix = matrix;
    //updateBBV();

}


const glm::mat4x4 SceneObject::getToWorldMatrix()
{

//   if(m_parent)
//   {
//     return m_parent->matrix * m_localTransformation.matrix;
//   }
   return m_parenTransformation.matrix ;
}

const glm::mat4x4 &SceneObject::getLocalMatrix()
{
    return m_localTransformation.matrix;
}


void SceneObject::setShape(Shape *shape)
{
   m_Shape = shape;
}


 Shape & SceneObject::getShape()
{
     return *m_Shape;
 }

 SceneObjectMaterial& SceneObject::getObjectMaterial()
 {
     return m_Material;
 }


