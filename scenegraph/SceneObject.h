#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "../shapes/Shape.h"
#include <memory>
#include "../lib/CS123SceneData.h"
#include "SceneObjectMaterial.h"


class SceneObject
{
public:
    SceneObject();
    SceneObject(Shape* shape, PrimitiveType,Material&);


    SceneObject(SceneObject&);
    ~SceneObject();

    void setPosition(Transformation position);
    void setOrientation(Transformation orientation);
    void setScale(Transformation scale);
    void setMaterial(Material scale);
    void setPrimitiveType(PrimitiveType primitiveType);

    Transformation& getPosition() const;
    Transformation& getOrientation() const;
    Transformation& getScale() const;
    Material& getMaterial();
    PrimitiveType& getPrimitiveType();

    void binTexture();
    void unBinTexture();

    void setParent(Transformation*& parent);
    Transformation& getParent();

    void addChild(SceneObject*& child);
    std::vector<SceneObject*>& getChildren();

    void setModelMatrix(const glm::mat4x4& matrix);
    void setWorldMatrix(const glm::mat4x4& matrix);

    const glm::mat4x4 getToWorldMatrix();
    const glm::mat4x4& getLocalMatrix();

//    glm::vec4 getPointWorldIntersection( HitPoint& h);
//    glm::vec4 getNormalWorldIntersection( glm::vec4& point);
//    void getPointWorldIntersection( HitPoint& h,glm::vec4& point,glm::vec4& normal);
    //void getWorldIntersection(HitPoint& h, glm::vec4& point, glm::vec4& normal);

    void setShape(Shape* shape);
    Shape& getShape();





    SceneObjectMaterial& getObjectMaterial();




protected:

    void updateBBV();

    Shape*  m_Shape;



    Transformation m_localTransformation;
    Transformation m_parenTransformation;


    PrimitiveType m_type;



    SceneObjectMaterial m_Material;

    Transformation* m_parent;
    std::vector<SceneObject*> children;



    //std::vector<float> bbv_vertices;

};

#endif // SCENEOBJECT_H
