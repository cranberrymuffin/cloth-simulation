#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "../lib/CS123SceneData.h"
#include "../shapes/Shape.h"
#include "SceneObjectMaterial.h"
#include <memory>

class SceneObject {
public:
    SceneObject();
    SceneObject(Shape* shape, PrimitiveType, Material&);

    SceneObject(SceneObject&);
    ~SceneObject();

    void setPosition(Transformation position);
    void setOrientation(Transformation orientation);
    void setScale(Transformation scale);
    void setMaterial(Material scale);
    void setPrimitiveType(PrimitiveType primitiveType);
    void settingsChanged();
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

    void setShape(Shape* shape);
    Shape& getShape();

    virtual void step(float deltaT);

    SceneObjectMaterial& getObjectMaterial();

    bool hasTexture();

    bool setHasTexture(bool hastext);

protected:
    void updateBBV();

    Shape* m_Shape;

    Transformation m_localTransformation;
    Transformation m_parenTransformation;

    PrimitiveType m_type;

    SceneObjectMaterial m_Material;

    Transformation* m_parent;
    std::vector<SceneObject*> children;

    bool m_hasTexture;
};

#endif // SCENEOBJECT_H
