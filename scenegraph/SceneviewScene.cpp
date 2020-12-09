#include "SceneviewScene.h"
#include "GL/glew.h"
#include "camera/Camera.h"
#include "gl/GLDebug.h"
#include <QGLWidget>

#include "Settings.h"
#include "SupportCanvas3D.h"
#include "gl/datatype/FBO.h"
#include "gl/shaders/CS123Shader.h"
#include "lib/ResourceLoader.h"
#include "scenegraph/Shapebuilder.h"
#include "shapes/Cloth.h"
#include "shapes/Sphere.h"

using namespace CS123::GL;

SceneviewScene::SceneviewScene()
{
    // TODO: [SCENEVIEW] Set up anything you need for your Sceneview scene here...
    initializeSceneLight();
    loadQuadShader();
    loadDepthShader();
    loadPhongShader();
    loadQuadShader();
    glm::vec3 eye(5.0, 5.0, 5.0);
    // glm::vec3 eye(5.0,5,-1.f);
    glm::vec3 fwd(0.0, 0.0, -1.0);
    glm::vec3 up(0.0, 1.0, 0.0);

    m_lookat = glm::lookAt(eye, fwd, up);
    m_projection = glm::perspective(
        glm::radians(45.0f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
        4.0f / 3.0f, // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
        0.1f, // Near clipping plane. Keep as big as possible, or you'll get precision issues.
        100.0f // Far clipping plane. Keep as little as possible.
    );

    m_enableKdtree = false;

    QImage image = QImage("/Users/aparnanatarajan/course/cs123/data/image/cheeseTexture.jpg");
    image = image.convertToFormat(QImage::Format_RGBX8888);
    QImage fImage = QGLWidget::convertToGLFormat(image);
    glGenTextures(1, &clothTexture);
    glBindTexture(GL_TEXTURE_2D, clothTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fImage.width(), fImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, fImage.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    initShadowFBO();

    initQuad();

    builPlaneCloth();

    builPointLigthObject();
}

SceneviewScene::~SceneviewScene()
{
}

void SceneviewScene::loadPhongShader()
{
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/default.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/default.frag");
    m_phongShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

void SceneviewScene::loadDepthShader()
{
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/depth.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/depth.frag");
    m_depthShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

void SceneviewScene::loadQuadShader()
{
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/quad.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/quad.frag");
    m_quadShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

void SceneviewScene::loadWireframeShader()
{
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/wireframe.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/wireframe.frag");
    m_wireframeShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

void SceneviewScene::loadNormalsShader()
{
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/normals.vert");
    std::string geometrySource = ResourceLoader::loadResourceFileToString(":/shaders/normals.gsh");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/normals.frag");
    m_normalsShader = std::make_unique<Shader>(vertexSource, geometrySource, fragmentSource);
}

void SceneviewScene::loadNormalsArrowShader()
{
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/normalsArrow.vert");
    std::string geometrySource = ResourceLoader::loadResourceFileToString(":/shaders/normalsArrow.gsh");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/normalsArrow.frag");
    m_normalsArrowShader = std::make_unique<Shader>(vertexSource, geometrySource, fragmentSource);
}

void SceneviewScene::render(Camera* camera)
{
    checkError();

    /* depth to FBO*/
    shadowPass();

    setClearColor();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_phongShader->bind();
    checkError();
    setSceneUniforms(*camera);
    checkError();
    setLights();
    checkError();

    renderGeometry();
    checkError();
    glBindTexture(GL_TEXTURE_2D, 0);

    renderPointLigthObject();
    checkError();
    m_phongShader->unbind();
}
void SceneviewScene::renderGeometryAsWireframe()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    renderGeometry();
}

void SceneviewScene::renderNormalsPass()
{
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

void SceneviewScene::renderGeometryAsFilledPolygons()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    renderGeometry();
}

void SceneviewScene::renderSceneViewObjects(const std::vector<SceneObject*>& s)
{

    for (size_t i = 0; i < s.size(); i++) {

        SceneObject* sceneObject = s[i];
        checkError();
        m_phongShader->setUniform("m", sceneObject->getToWorldMatrix());

        checkError();
        Material m = sceneObject->getMaterial();
        m.cDiffuse *= m_globalData.kd;
        m.cAmbient *= m_globalData.ka;
        m_phongShader->applyMaterial(m);

        if (sceneObject->getMaterial().textureMap.isUsed) {
            sceneObject->binTexture();
        }
        checkError();
        m_phongShader->setUniform("lightSpaceMatrix", lightSpaceMatrix);

        checkError();
        GLint location = glGetUniformLocation(m_phongShader->getID(), "shadowMap");

        glUniform1i(location, 1);
        checkError();
        glActiveTexture(GL_TEXTURE1);
        checkError();
        glBindTexture(GL_TEXTURE_2D, depthMap);

        location = glGetUniformLocation(m_phongShader->getID(), "tex");
        glUniform1i(location, 0);
        checkError();
        glActiveTexture(GL_TEXTURE0);
        checkError();
        glBindTexture(GL_TEXTURE_2D, clothTexture);

        // std::cout << "SceneviewScene::renderSceneViewObjects 3" << std::endl;
        checkError();
        glDisable(GL_CULL_FACE);
        sceneObject->getShape().draw();
        checkError();
        glEnable(GL_CULL_FACE);
        // std::cout << "SceneviewScene::renderSceneViewObjects 4" << std::endl;
        checkError();

        renderSceneViewObjects(sceneObject->getChildren());
    }
}

void SceneviewScene::renderDepthSceneViewObjects(const std::vector<SceneObject*>& s)
{
    for (size_t i = 0; i < s.size(); i++) {

        SceneObject* sceneObject = s[i];
        m_depthShader->setUniform("m", sceneObject->getToWorldMatrix());
        glDisable(GL_CULL_FACE);
        sceneObject->getShape().draw();
        glEnable(GL_CULL_FACE);
        renderSceneViewObjects(sceneObject->getChildren());
    }
}

void SceneviewScene::setSceneUniforms(Camera& camera)
{

    // m_phongShader->setUniform("useLighting", settings.useLighting);
    // m_phongShader->setUniform("useArrowOffsets", false);
    m_phongShader->setUniform("p", m_projection);
    m_phongShader->setUniform("v", m_lookat);
}

void SceneviewScene::setMatrixUniforms(Shader* shader, Camera& camera)
{
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
    for (size_t i = 0; i < m_lights.size(); i++) {
        m_phongShader->setLight(m_lights[i]);
    }
}

void SceneviewScene::renderGeometry()
{

    checkError();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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

void SceneviewScene::settingsChanged()
{
    for (size_t i = 0; i < m_sceneObjects.size(); ++i) {
        m_sceneObjects[i]->settingsChanged();
    }
}

void SceneviewScene::update(float deltaTime)
{
    for (size_t i = 0; i < m_sceneObjects.size(); ++i) {
        m_sceneObjects[i]->step(deltaTime);
    }
}

void SceneviewScene::shadowPass()
{

    float near_plane = 1.0f, far_plane = 100.5f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

    glm::mat4 lightView = glm::lookAt(m_pointLight.pos.xyz(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0));
    lightSpaceMatrix = lightProjection * lightView;

    m_depthShader->bind();
    checkError();
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    m_depthShader->setUniform("lightSpaceMatrix", lightSpaceMatrix);
    checkError();
    renderDepthSceneViewObjects(m_sceneObjects);
    checkError();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    m_depthShader->unbind();
    checkError();
    glViewport(0, 0, m_width * m_aspect, m_height * m_aspect);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SceneviewScene::initQuad()
{
    float quadVertices[] = {
        // positions        // texture Coords
        -1.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        -1.0f,
        -1.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        1.0f,
        -1.0f,
        0.0f,
        1.0f,
        0.0f,
    };
    // setup plane VAO
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

void SceneviewScene::renderQuad()
{
    m_quadShader->bind();
    checkError();
    GLint location = glGetUniformLocation(m_quadShader->getID(), "near_plane");
    checkError();
    glUniform1f(location, 1.0);
    checkError();
    location = glGetUniformLocation(m_quadShader->getID(), "far_plane");
    checkError();
    glUniform1f(location, 10.f);
    checkError();
    /*m_quadShader->setUniform("near_plane", 1.f);
    checkError();
    m_quadShader->setUniform("far_plane", 10.f);
    checkError();*/
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, clothTexture);
    checkError();
    glBindVertexArray(quadVAO);
    checkError();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
    m_quadShader->unbind();
}

void SceneviewScene::AddCloth()
{

    Material m;
    m.cDiffuse = glm::vec4(0.7, 0.4, 0.4, 1.0);
    m.cAmbient = glm::vec4(0.25, 0.25, 0.25, 1.0);
    m.cSpecular = glm::vec4(0.8, 0.8, 0.8, 1.0);
    m.shininess = 20;

    Shape* clothShape = new Cloth(25, 1, 1);
    m_cloth = new SceneObject(clothShape, PrimitiveType::PRIMITIVE_MESH, m);
    m_cloth->setWorldMatrix(glm::mat4x4());
    m_sceneObjects.push_back(m_cloth);

    m_clothObject = m_cloth;
}

void SceneviewScene::builScenePlane()
{
    Material m;
    m.cDiffuse = glm::vec4(0.8, 0.3, 0.2, 1.0);
    m.cAmbient = glm::vec4(0.25, 0.25, 0.25, 1.0);
    m.cSpecular = glm::vec4(0.8, 0.8, 0.8, 1.0);
    m.shininess = 20;

    Shape* floorShape = ShapeBuilder::getInstance().LoadShape(PrimitiveType::PRIMITIVE_CUBE, 8, 8);
    SceneObject* floor = new SceneObject(floorShape, PrimitiveType::PRIMITIVE_CUBE, m);
    glm::mat4x4 tr = glm::translate(glm::mat4x4(), glm::vec3(0.0, -1.0, 0.0));
    tr = glm::scale(tr, glm::vec3(6.0, 0.2, 6.0));
    floor->setWorldMatrix(tr);
    m_sceneObjects.push_back(floor);

    Shape* cube2Shape = ShapeBuilder::getInstance().LoadShape(PrimitiveType::PRIMITIVE_CUBE, 8, 8);
    SceneObject* sceneObj2 = new SceneObject(cube2Shape, PrimitiveType::PRIMITIVE_CUBE, m);
    glm::mat4x4 tr2 = glm::translate(glm::mat4x4(), glm::vec3(0.0, 1.5, -0.5));
    sceneObj2->setWorldMatrix(tr2);
    m_sceneObjects.push_back(sceneObj2);

    Shape* cube3Shape = ShapeBuilder::getInstance().LoadShape(PrimitiveType::PRIMITIVE_CUBE, 8, 8);
    SceneObject* sceneObj3 = new SceneObject(cube3Shape, PrimitiveType::PRIMITIVE_CUBE, m);
    glm::mat4x4 tr3 = glm::translate(glm::mat4x4(), glm::vec3(0.0, 1.5, 1.5));
    sceneObj3->setWorldMatrix(tr3);
    m_sceneObjects.push_back(sceneObj3);

    Shape* cube4Shape = ShapeBuilder::getInstance().LoadShape(PrimitiveType::PRIMITIVE_CUBE, 8, 8);
    SceneObject* sceneObj4 = new SceneObject(cube4Shape, PrimitiveType::PRIMITIVE_CUBE, m);
    glm::mat4x4 tr4 = glm::translate(glm::mat4x4(), glm::vec3(1.0, 0.8, 1.5));
    sceneObj3->setWorldMatrix(tr4);
    m_sceneObjects.push_back(sceneObj4);
}

void SceneviewScene::builPlaneCloth()
{
    AddCloth();
    //    Material m;
    //    m.cDiffuse = glm::vec4(0.8,0.3,0.2,1.0);
    //    m.cAmbient = glm::vec4(0.25,0.25,0.25,1.0);
    //    m.cSpecular = glm::vec4(0.8,0.8,0.8,1.0);
    //    m.shininess = 20;

    //    Shape* cube2Shape = ShapeBuilder::getInstance().LoadShape(PrimitiveType::PRIMITIVE_CUBE,8,8);
    //    SceneObject* sceneObj2 = new SceneObject(cube2Shape,PrimitiveType::PRIMITIVE_CUBE,m);
    //    glm::mat4x4 tr2 = glm::translate(glm::mat4x4(),glm::vec3(0.0,0.1,0.1));
    //    sceneObj2->setWorldMatrix(tr2);
    //    m_sceneObjects.push_back(sceneObj2);

    Material m2;
    m2.cDiffuse = glm::vec4(0.5, 0.4, 0.5, 1.0);
    m2.cAmbient = glm::vec4(0.25, 0.25, 0.25, 1.0);
    m2.cSpecular = glm::vec4(0.8, 0.8, 0.8, 1.0);
    m2.shininess = 20;

    Shape* wallShape = ShapeBuilder::getInstance().LoadShape(PrimitiveType::PRIMITIVE_CUBE, 8, 8);
    SceneObject* floor = new SceneObject(wallShape, PrimitiveType::PRIMITIVE_CUBE, m2);
    glm::mat4x4 tr = glm::translate(glm::mat4x4(), glm::vec3(-15.0, -15.0, -5.0));
    tr = glm::rotate(tr, glm::radians(90.f), glm::vec3(1.0, 0.0, 0.0));
    tr = glm::scale(tr, glm::vec3(100.0, 0.2, 100.0));
    floor->setWorldMatrix(tr);
    m_sceneObjects.push_back(floor);
}

void SceneviewScene::builPointLigthObject()
{
    Material m;
    m.cDiffuse = glm::vec4(0.8, 0.8, 0.8, 1.0);
    m.cAmbient = glm::vec4(0.25, 0.25, 0.25, 1.0);
    m.cSpecular = glm::vec4(0.0, 0.0, 0.0, 1.0);
    m.shininess = 20;

    Shape* sphShape = ShapeBuilder::getInstance().LoadShape(PrimitiveType::PRIMITIVE_SPHERE, 8, 8);
    glm::mat4 tr = glm::scale(glm::mat4(), glm::vec3(5, 5, 5));
    m_ligthObject = std::make_unique<SceneObject>(sphShape, PrimitiveType::PRIMITIVE_SPHERE, m);
    m_ligthObject->setWorldMatrix(tr);
}

void SceneviewScene::renderPointLigthObject()
{

    glm::mat4x4 tr = glm::translate(m_pointLight.pos.xyz());
    glm::mat4x4 scal = m_ligthObject->getToWorldMatrix();

    m_phongShader->setUniform("m", scal * tr);

    checkError();
    Material m = m_ligthObject->getMaterial();
    m.cDiffuse *= m_globalData.kd;
    m.cAmbient *= m_globalData.ka;
    m_phongShader->applyMaterial(m);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    m_ligthObject->getShape().draw();
}

void SceneviewScene::initShadowFBO()
{
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture

    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SceneviewScene::initializeSceneLight()
{
    m_globalData.kd = 0.5;
    m_globalData.ka = 0.75;
    m_globalData.ks = 0.5;

    m_pointLight.type = LightType::LIGHT_POINT;
    m_pointLight.pos = glm::vec4(0, 0, 8.1, 1.0);
    m_pointLight.color = glm::vec4(1.0, 1.0, 1.0, 1.0);
    m_pointLight.id = 0;

    m_lights.push_back(m_pointLight);
}
