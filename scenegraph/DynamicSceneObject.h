#ifndef DYNAMICSCENEOBJECT_H
#define DYNAMICSCENEOBJECT_H

#include "scenegraph/SceneObject.h"

class DynamicSceneObject:public SceneObject
{
public:
    DynamicSceneObject();

    DynamicSceneObject(Shape* shape, PrimitiveType,Material&);


};

#endif // DYNAMICSCENEOBJECT_H
