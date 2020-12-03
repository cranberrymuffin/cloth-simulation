#ifndef SCENE_H
#define SCENE_H

#include "lib/CS123SceneData.h"
#include <memory>
#include "shapes/Shape.h"
#include <map>
#include "SceneObject.h"

class Camera;
class CS123ISceneParser;


/**
 * @class Scene
 *
 * @brief This is the base class for all scenes. Modify this class if you want to provide
 * common functionality to all your scenes.
 *
 */

typedef CS123SceneLightData LightData;
typedef CS123ScenePrimitive Primitive;
typedef CS123SceneGlobalData GlobalData;
typedef CS123SceneNode SceneNode;


class Scene {
public:
    Scene();
    Scene(Scene &scene);
    virtual ~Scene();

    virtual void settingsChanged() {}

    static void parse(Scene *sceneToFill, CS123ISceneParser *parser);


protected:

    // Adds a primitive to the scene.
    virtual void addPrimitive(const CS123ScenePrimitive &scenePrimitive, const glm::mat4x4 &l_matrix, const glm::mat4x4 &w_matrix);

    // Adds a light to the scene.
    virtual void addLight(const CS123SceneLightData &sceneLight);

    // Sets the global data for the scene.
    virtual void setGlobal(const CS123SceneGlobalData &global);


    void addSceneObject(Shape *shape,PrimitiveType type,Material material,
                                         const glm::mat4x4 &l_matrix,
                                         const glm::mat4x4 &w_matrix);

    void loadMeshfile(const std::string& meshFile,
                      PrimitiveType,Material,const glm::mat4x4 &l_matrix,
                      const glm::mat4x4 &w_matrix);

   std::map<PrimitiveType,Shape*> m_shapes;

   std::vector<SceneObject*> m_sceneObjects;
   std::vector<LightData> m_lights;

   CS123SceneGlobalData m_globalData;


   std::vector<SceneObject*> m_kdtree;


   void createKdTree();


   bool m_enableKdtree;

private:
   void traverseSceneGraph(Scene * sceneToFill , SceneNode* node, glm::mat4 parent);

};

#endif // SCENE_H
