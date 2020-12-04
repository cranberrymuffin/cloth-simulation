#include "SceneviewScene.h"
#include "GL/glew.h"
#include <QGLWidget>
#include "gl/GLDebug.h"
#include "camera/Camera.h"

#include "Settings.h"
#include "SupportCanvas3D.h"
#include "lib/ResourceLoader.h"
#include "gl/shaders/CS123Shader.h"
#include "lib/ResourceLoader.h"
#include "shapes/Cloth.h"
#include "shapes/PlaneShape.h"
using namespace CS123::GL;


SceneviewScene::SceneviewScene()
{
    // TODO: [SCENEVIEW] Set up anything you need for your Sceneview scene here...
    initializeSceneLight();
    loadPhongShader();
    glm::vec3 eye(0.0,0.0,5.0);
    glm::vec3 fwd(0.0,0.0,-1.0);
    glm::vec3 up(0.0,1.0,0.0);

    m_lookat = glm::lookAt(eye,fwd,up);
    m_projection = glm::perspective(
        glm::radians(45.0f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
        4.0f / 3.0f,       // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
        0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
        100.0f             // Far clipping plane. Keep as little as possible.
    );

    m_enableKdtree = false;
  //  std::string inputfile = "D:/cs1230/cs1230-final-project/resources/models/cornell_box.obj";
//
    //ResourceLoader::readObjFile(m_sceneObjects,inputfile );
    Material m;

    Shape *clothShape = new Cloth(7,7,1,1,1,0.3);
   // Shape* buildShape = new PlaneShape(5,1,1);
    m_cloth = new SceneObject(clothShape,PrimitiveType::PRIMITIVE_MESH,m);
    m_cloth->setWorldMatrix(glm::mat4x4());
    m_sceneObjects.push_back(m_cloth);
}

SceneviewScene::~SceneviewScene()
{

}

void SceneviewScene::loadPhongShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/default.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/default.frag");
    m_phongShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

void SceneviewScene::loadWireframeShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/wireframe.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/wireframe.frag");
    m_wireframeShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

void SceneviewScene::loadNormalsShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/normals.vert");
    std::string geometrySource = ResourceLoader::loadResourceFileToString(":/shaders/normals.gsh");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/normals.frag");
    m_normalsShader = std::make_unique<Shader>(vertexSource, geometrySource, fragmentSource);
}

void SceneviewScene::loadNormalsArrowShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/normalsArrow.vert");
    std::string geometrySource = ResourceLoader::loadResourceFileToString(":/shaders/normalsArrow.gsh");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/normalsArrow.frag");
    m_normalsArrowShader = std::make_unique<Shader>(vertexSource, geometrySource, fragmentSource);
}

void SceneviewScene::render(Camera* camera) {
    checkError();
    setClearColor();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_phongShader->bind();
    std::cout<<"SceneviewScene::render 0" << std::endl;
    checkError();
    setSceneUniforms(*camera);
    std::cout<<"SceneviewScene::render 1" << std::endl;
    checkError();
   //  setLights();
    std::cout<<"SceneviewScene::render 2" << std::endl;
    checkError();
    renderGeometry();
    std::cout<<"SceneviewScene::render 3" << std::endl;
    checkError();
    glBindTexture(GL_TEXTURE_2D, 0);
    m_phongShader->unbind();

//    m_wireframeShader->bind();
//    m_wireframeShader->setUniform("p", m_camera->getProjectionMatrix());
//    m_wireframeShader->setUniform("v", m_camera->getViewMatrix());

//    m_wireframeShader->unbind();

//    if (settings.drawNormals) {
//        renderNormalsPass();
//    }

//    if(m_enableKdtree)
//    {
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//        m_wireframeShader->setUniform("m",glm::mat4x4());

//    }

}
void SceneviewScene::renderGeometryAsWireframe() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    renderGeometry();
}

void SceneviewScene::renderNormalsPass () {
    // Render the lines.
    m_normalsShader->bind();
    setMatrixUniforms(m_normalsShader.get(), *m_camera);
    renderGeometryAsWireframe();
    m_normalsShader->unbind();

    // Render the arrows.
    m_normalsArrowShader->bind();
    setMatrixUniforms(m_normalsArrowShader.get(), *m_camera);
    renderGeometryAsFilledPolygons();
    m_normalsArrowShader->unbind();
}

void SceneviewScene::renderGeometryAsFilledPolygons() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    renderGeometry();
}


void SceneviewScene::renderSceneViewObjects( const std::vector<SceneObject*> &s)
{

    for(size_t i = 0 ; i < s.size();i++)
    {

         SceneObject* sceneObject = m_sceneObjects[i];
         std::cout << "SceneviewScene::renderSceneViewObjects 1" << std::endl;
        checkError();
         m_phongShader->setUniform("m",sceneObject->getToWorldMatrix());
         std::cout << "SceneviewScene::renderSceneViewObjects 2" << std::endl;
        checkError();
         Material m =sceneObject->getMaterial() ;
         m.cDiffuse *= m_globalData.kd;
         m.cAmbient *= m_globalData.ka;
        // m_phongShader->applyMaterial(m);

         if(sceneObject->getMaterial().textureMap.isUsed)
         {
            sceneObject->binTexture();
         }
         std::cout << "SceneviewScene::renderSceneViewObjects 3" << std::endl;
        checkError();
         sceneObject->getShape().draw();
          std::cout << "SceneviewScene::renderSceneViewObjects 4" << std::endl;
         checkError();

         renderSceneViewObjects(sceneObject->getChildren());
    }
}

void SceneviewScene::setSceneUniforms(Camera& camera) {


   // m_phongShader->setUniform("useLighting", settings.useLighting);
   // m_phongShader->setUniform("useArrowOffsets", false);
    m_phongShader->setUniform("p" , m_projection);
    m_phongShader->setUniform("v", m_lookat);
}

void SceneviewScene::setMatrixUniforms(Shader *shader, Camera& camera) {
    shader->setUniform("p", camera.getProjectionMatrix());
    shader->setUniform("v", camera.getViewMatrix());
}

void SceneviewScene::setLights()
{
    // TODO: [SCENEVIEW] Fill this in...
    //
    // Set up the lighting for your scene using m_phongShader.
    // The lighting information will most likely be stored in CS123SceneLightData structures.
    //
    for(size_t i = 0; i< m_lights.size();i++)
    {
      m_phongShader->setLight(m_lights[i]);
    }


}

void SceneviewScene::renderGeometry() {

    std::cout << "SceneviewScene::renderGeometry 0" << std::endl;
    checkError();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    std::cout << "SceneviewScene::renderGeometry 1" << std::endl;
    checkError();

    // TODO: [SCENEVIEW] Fill this in...
    // You shouldn't need to write *any* OpenGL in this class!
    //
    //
    // This is where you should render the geometry of the scene. Use what you
    // know about OpenGL and leverage your Shapes classes to get the job done.
    //
    renderSceneViewObjects(m_sceneObjects);

}


void SceneviewScene::settingsChanged() {
    // TODO: [SCENEVIEW] Fill this in if applicable.
}

void SceneviewScene::update(float deltaTime)
{
  m_cloth->step(deltaTime);
}

void SceneviewScene::initializeSceneLight()
{
    CS123SceneLightData m_light;
    m_light.type = LightType::LIGHT_DIRECTIONAL;
    m_light.dir = glm::normalize(glm::vec4(1.f, -1.f, -1.f, 0.f));
    m_light.color.r = m_light.color.g = m_light.color.b = 1;
    m_light.id = 0;

    m_lights.push_back(m_light);
}

