#include "DynamicSceneObject.h"

DynamicSceneObject::DynamicSceneObject()
{

}

DynamicSceneObject::DynamicSceneObject(Shape *shape, PrimitiveType p, Material & m)
    :SceneObject(shape,p,m)
{

}

