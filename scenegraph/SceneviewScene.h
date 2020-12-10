#ifndef SCENEVIEWSCENE_H
#define SCENEVIEWSCENE_H

#include "OpenGLScene.h"

#include <memory>


namespace CS123 { namespace GL {

    class Shader;
    class CS123Shader;
    class Texture2D;
    class FBO;
}}
using namespace CS123::GL;
/**
 *
 * @class SceneviewScene
 *
 * A complex scene consisting of multiple objects. Students will implement this class in the
 * Sceneview assignment.
 *
 * Here you will implement your scene graph. The structure is up to you - feel free to create new
 * classes and data structures as you see fit. We are providing this SceneviewScene class for you
 * to use as a stencil if you like.
 *
 * Keep in mind that you'll also be rendering entire scenes in the next two assignments, Intersect
 * and Ray. The difference between this assignment and those that follow is here, we are using
 * OpenGL to do the rendering. In Intersect and Ray, you will be responsible for that.
 */
class SceneviewScene : public OpenGLScene {
public:
    SceneviewScene();
    virtual ~SceneviewScene();

    virtual void render(Camera*) override;
    void renderNormalsPass ();
    void renderGeometryAsWireframe();
    void renderSceneViewObjects( const std::vector<SceneObject*>& s);
    void renderDepthSceneViewObjects( const std::vector<SceneObject*>& s);




    void renderGeometryAsFilledPolygons();
    virtual void settingsChanged() override;

    // Use this method to set an internal selection, based on the (x, y) position of the mouse
    // pointer.  This will be used during the "modeler" lab, so don't worry about it for now.
    void setSelection(int x, int y);

    void update(float deltaTime);



private:
    void shadowPass();

    void initQuad();
    void renderQuad();

    void AddCloth();

    void builScenePlane();
    void builPlaneCloth();

    void builPointLigthObject();
    void renderPointLigthObject();

    void initShadowFBO();

    void initializeSceneLight();
    void loadPhongShader();
    void loadDepthgShader();
    void loadQuadShader();

    void loadWireframeShader();
    void loadNormalsShader();
    void loadNormalsArrowShader();

    void setSceneUniforms(Camera& );
    void setMatrixUniforms(CS123::GL::Shader *shader,Camera&);
    void setLights();
    void renderGeometry();

    glm::mat4 buildProjectorMatrices();

    std::unique_ptr<Camera> m_camera;

    std::unique_ptr<CS123::GL::CS123Shader> m_phongShader;
    std::unique_ptr<CS123::GL::CS123Shader> m_depthshader;
    std::unique_ptr<CS123::GL::CS123Shader> m_quadShader;

    std::unique_ptr<CS123::GL::Shader> m_wireframeShader;
    std::unique_ptr<CS123::GL::Shader> m_normalsShader;
    std::unique_ptr<CS123::GL::Shader> m_normalsArrowShader;
    glm::mat4x4 m_lookat;
    glm::mat4x4 m_projection;
    SceneObject* m_cloth;

    std::shared_ptr<FBO> depthFBO;
    unsigned int depthMapFBO;
    unsigned int depthMap;
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

    std::unique_ptr<SceneObject> m_ligthObject;
    SceneObject* m_clothObject;

    LightData m_pointLight;
    glm::mat4 lightSpaceMatrix;

    unsigned int quadVAO = 0;
    unsigned int quadVBO;

    glm::mat4 projectiveTextureMatrix;

    std::unique_ptr<CS123::GL::Texture2D> prjtexture;
    unsigned int pjTextId;


};

#endif // SCENEVIEWSCENE_H
