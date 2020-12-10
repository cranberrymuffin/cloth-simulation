#include "CS123Shader.h"

#include "lib/CS123SceneData.h"
#include "ui/Settings.h"


#include "gl/GLDebug.h"
#include <sstream>
#include <iostream>
#include "common/common.h"
#include "glm/gtc/type_ptr.hpp"

namespace CS123 { namespace GL {


CS123Shader::CS123Shader(const std::string &vertexSource, const std::string &fragmentSource) :
    Shader(vertexSource, fragmentSource)
{
}

CS123Shader::CS123Shader(const std::string &vertexSource, const std::string &geometrySource, const std::string &fragmentSource) :
    Shader(vertexSource, geometrySource, fragmentSource)
{
}

glm::vec3 toGLMVec3(const CS123SceneColor &c) {
    return glm::vec3(c.r, c.g, c.b);
}

void CS123Shader::applyMaterial(const CS123SceneMaterial &material) {
    checkError();
    int lc = glGetUniformLocation(getID(),"ambient_color");
    std::cout << lc << std::endl;
    glm::vec3 ca = toGLMVec3(material.cAmbient);
    glUniform3fv(lc, 1, glm::value_ptr(ca));

    //setUniform("ambient_color", toGLMVec3(material.cAmbient));
    checkError();
     lc = glGetUniformLocation(getID(),"diffuse_color");
     std::cout << lc << std::endl;
     glm::vec3 cd = toGLMVec3(material.cDiffuse);
     glUniform3fv(lc, 1, glm::value_ptr(cd));
 //  setUniform("diffuse_color", toGLMVec3(material.cDiffuse));
    checkError();
    lc = glGetUniformLocation(getID(),"specular_color");
    std::cout << lc << std::endl;
    glm::vec3 ce = toGLMVec3(material.cSpecular);
    glUniform3fv(lc, 1, glm::value_ptr(ce));
   //setUniform("specular_color", toGLMVec3(material.cSpecular));
    checkError();
    lc = glGetUniformLocation(getID(),"shininess");
    std::cout << lc << std::endl;
    glUniform1f(lc,  material.shininess);
    //setUniform("shininess", material.shininess);
    checkError();
}

void CS123Shader::setLight(const CS123SceneLightData &light) {
    bool ignoreLight = false;

    GLint lightType;
    std::string name;
    glm::vec3 ndir;
    switch(light.type) {
        case LightType::LIGHT_POINT:
            lightType = 0;
            name = "lightPositions";
            setUniformArrayByIndex(name, light.pos.xyz(), light.id);
            //std::cout<<"CS123Shader::setLight 0" << std::endl;
            checkError();
           // if (!settings.usePointLights) ignoreLight = true;
            break;
        case LightType::LIGHT_DIRECTIONAL:
            lightType = 1;
            ndir = glm::normalize(light.dir.xyz());
            name = "lightDirections";
            setUniformArrayByIndex(name, ndir, light.id);
            if (!settings.useDirectionalLights) ignoreLight = true;
            break;
        default:
            lightType = 0;
            ignoreLight = true; // Light type not supported
            break;
    }

    CS123SceneColor color = light.color;
   // if (ignoreLight) color.r = color.g = color.b = 0;
    std::cout<<"CS123Shader::setLight 1" << std::endl;
    checkError();
    //setUniformArrayByIndex("lightTypes", lightType, light.id);
    std::cout<<"CS123Shader::setLight 2" << std::endl;
    checkError();
    //GLint l = glGetUniformLocation(getID(),"mylightColor");
    //glUniform3fv(l, 1, glm::value_ptr(glm::vec3(color.r, color.g,color.b)));
    setUniformArrayByIndex("lightColors", glm::vec3(color.r, color.g, color.b), light.id);
    std::cout<<"CS123Shader::setLight 3" << std::endl;
    checkError();
//    setUniformArrayByIndex("lightAttenuations", light.function, light.id);
}

}}
