#include "Scene.h"
#include "camera/Camera.h"
#include "lib/CS123ISceneParser.h"

#include "SceneObject.h"
#include "glm/gtx/transform.hpp"
#include "lib/ResourceLoader.h"
#include "scenegraph/Shapebuilder.h"
#include <iostream>

#define ERROR_NO_SHAPE(e) "Shape not supported "

Scene::Scene()
{
    std::cout << "Scene()" << std::endl;
}

Scene::Scene(Scene& other)
{
    // We need to set the global constants to one when we duplicate a scene,
    // otherwise the global constants will be double counted (squared)
    CS123SceneGlobalData global;
    global.ka = other.m_globalData.ka;
    global.kd = other.m_globalData.kd;
    global.ks = other.m_globalData.ks;
    global.kt = other.m_globalData.kt;
    setGlobal(global);

    // TODO [INTERSECT]
    // Make sure to copy over the lights and the scenegraph from the old scene,
    // as well as any other member variables your new scene will need.
    this->m_lights = other.m_lights;

    for (size_t i = 0; i < other.m_sceneObjects.size(); i++) {
        SceneObject* sceneObject = new SceneObject(*other.m_sceneObjects[i]);

        this->m_sceneObjects.push_back(sceneObject);
    }
}

Scene::~Scene()
{
    // Do not delete m_camera, it is owned by SupportCanvas3D

    for (int i = 0; i < m_sceneObjects.size(); i++) {
        delete m_sceneObjects[i];
    }
}

void Scene::parse(Scene* sceneToFill, CS123ISceneParser* parser)
{
    // TODO: load scene into sceneToFill using setGlobal(), addLight(), addPrimitive(), and
    // get global data

    parser->getGlobalData(sceneToFill->m_globalData);

    // get lights
    int numLigths = parser->getNumLights();
    sceneToFill->m_lights = std::vector<LightData>(numLigths);
    for (int i = 0; i < numLigths; ++i) {
        LightData light;
        parser->getLightData(i, sceneToFill->m_lights[i]);
    }

    SceneNode* rootNode = parser->getRootNode();
    glm::mat4x4 parentMatrix;
    sceneToFill->traverseSceneGraph(sceneToFill, rootNode, parentMatrix);

    //   finishParsing()
}

void Scene::addPrimitive(const CS123ScenePrimitive& scenePrimitive, const glm::mat4x4& l_matrix, const glm::mat4x4& w_matrix)
{

    int param1 = 0;
    int param2 = 0;
    Shape* shape = nullptr;
    switch (scenePrimitive.type) {
    case PrimitiveType::PRIMITIVE_CONE:
        param1 = param2 = 4;
        shape = ShapeBuilder::getInstance().LoadShape(scenePrimitive.type, param1, param2);
        addSceneObject(shape, scenePrimitive.type, scenePrimitive.material, l_matrix, w_matrix);
        break;
    case PrimitiveType::PRIMITIVE_CUBE:
        param1 = param2 = 3;
        shape = ShapeBuilder::getInstance().LoadShape(scenePrimitive.type, param1, param2);
        addSceneObject(shape, scenePrimitive.type, scenePrimitive.material, l_matrix, w_matrix);
        break;
    case PrimitiveType::PRIMITIVE_CYLINDER:
        param1 = param2 = 6;
        shape = ShapeBuilder::getInstance().LoadShape(scenePrimitive.type, param1, param2);
        addSceneObject(shape, scenePrimitive.type, scenePrimitive.material, l_matrix, w_matrix);
        break;
    case PrimitiveType::PRIMITIVE_SPHERE:
        param1 = param2 = 9;
        shape = ShapeBuilder::getInstance().LoadShape(scenePrimitive.type, param1, param2);
        addSceneObject(shape, scenePrimitive.type, scenePrimitive.material, l_matrix, w_matrix);
        break;
    case PrimitiveType::PRIMITIVE_MESH:
        loadMeshfile(scenePrimitive.meshfile, scenePrimitive.type, scenePrimitive.material, l_matrix, w_matrix);
        break;
    default:
        break;
    }

    //PrimitiveType type = scenePrimitive.type;
    // CS123SceneMaterial material = scenePrimitive.material;

    //    SceneObject* sceneObject = new SceneObject(shape,type,
    //            material,rayShapeTester);
    //    sceneObject->setModelMatrix(l_matrix);
    //    sceneObject->setWorldMatrix(w_matrix);
    //    m_sceneObjects.push_back(sceneObject);
}

void Scene::addLight(const CS123SceneLightData& sceneLight)
{

    m_lights.push_back(sceneLight);
}

void Scene::setGlobal(const CS123SceneGlobalData& global)
{
    m_globalData.ka = global.ka;
    m_globalData.kd = global.kd;
    m_globalData.ks = global.ks;
    m_globalData.kt = global.kt;
}

void Scene::addSceneObject(Shape* shape, PrimitiveType type, Material material, const glm::mat4x4& l_matrix, const glm::mat4x4& w_matrix)
{
    SceneObject* sceneObject = new SceneObject(shape, type,
        material);
    sceneObject->setModelMatrix(l_matrix);
    sceneObject->setWorldMatrix(w_matrix);
    m_sceneObjects.push_back(sceneObject);
}

void Scene::loadMeshfile(const std::string& meshFile, PrimitiveType, Material, const glm::mat4x4& l_matrix, const glm::mat4x4& w_matrix)
{
    ResourceLoader::readObjFile(m_sceneObjects, meshFile);
    //reasign materials
}

void Scene::traverseSceneGraph(Scene* sceneToFill, SceneNode* node, glm::mat4 parent)
{
    if (!node) {
        return;
    }
    // Tree preorder traversal
    glm::mat4 transformationMatrix;
    glm::mat4 t;
    glm::mat4 r;
    glm::mat4 s;

    for (int i = 0; i < node->transformations.size(); ++i) {
        Transformation* transformation = node->transformations[i];

        switch (transformation->type) {
        case TransformationType::TRANSFORMATION_MATRIX:
            transformationMatrix = transformationMatrix * transformation->matrix;
            break;
        case TransformationType::TRANSFORMATION_SCALE:
            transformationMatrix = glm::scale(transformationMatrix, transformation->scale);
            break;
        case TransformationType::TRANSFORMATION_ROTATE:
            transformationMatrix = glm::rotate(transformationMatrix, transformation->angle, transformation->rotate);
            break;
        case TransformationType::TRANSFORMATION_TRANSLATE:
            transformationMatrix = glm::translate(transformationMatrix, transformation->translate);
            break;
        default:
            break;
        }
    }

    glm::mat4 local = transformationMatrix;
    glm::mat4 worldTransformation = parent * local;

    for (size_t i = 0; i < node->primitives.size(); ++i) {

        Primitive* p = node->primitives[i];

        sceneToFill->addPrimitive(*p, local, worldTransformation);
    }

    for (size_t i = 0; i < node->children.size(); ++i) {
        traverseSceneGraph(sceneToFill, node->children[i], worldTransformation);
    }
}
