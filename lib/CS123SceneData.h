/**
 * @file CS123SceneData.h
 *
 * Header file containing scene data structures.
 */

#ifndef __CS123_SCENE_DATA__
#define __CS123_SCENE_DATA__

#include <vector>
#include <string>

#include "glm/glm.hpp"

enum class LightType {
    LIGHT_POINT, LIGHT_DIRECTIONAL, LIGHT_SPOT, LIGHT_AREA
};

enum class PrimitiveType {
    PRIMITIVE_CUBE,
    PRIMITIVE_CONE,
    PRIMITIVE_CYLINDER,
    PRIMITIVE_TORUS,
    PRIMITIVE_SPHERE,
    PRIMITIVE_MESH
};

// Enumeration for types of transformations that can be applied to objects, lights, and cameras.
enum TransformationType {
   TRANSFORMATION_TRANSLATE, TRANSFORMATION_SCALE, TRANSFORMATION_ROTATE, TRANSFORMATION_MATRIX
};

template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type< Enumeration >::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

// Struct to store a RGBA color in floats [0,1]
using CS123SceneColor = glm::vec4;

// Scene global color coefficients
struct CS123SceneGlobalData  {
   float ka;  // global ambient coefficient
   float kd;  // global diffuse coefficient
   float ks;  // global specular coefficient
   float kt;  // global transparency coefficient

   CS123SceneGlobalData(){};

   CS123SceneGlobalData(CS123SceneGlobalData& other):ka(other.ka),kd(other.kd),ks(other.ks),kt(other.kt)
   {

   }
   void operator=(const CS123SceneGlobalData& other)
   {
       ka = other.ka;
       kd = other.kd;
       ks = other.ks;
       kt = other.kt;
   }
   void operator=(CS123SceneGlobalData& other)
   {
        ka = other.ka;
        kd = other.kd;
        ks = other.ks;
        kt = other.kt;
   }
};

// Data for a single light
struct CS123SceneLightData {
   int id;
   LightType type;

   CS123SceneColor color;
   glm::vec3 function;  // Attenuation function

   glm::vec4 pos;       // Not applicable to directional lights
   glm::vec4 dir;       // Not applicable to point lights

   float radius;        // Only applicable to spot lights
   float penumbra;      // Only applicable to spot lights
   float angle;         // Only applicable to spot lights

   float width, height; // Only applicable to area lights
   CS123SceneLightData(){};
   CS123SceneLightData(const CS123SceneLightData& other): id (other.id),
       type( other.type),
       color(other.color),
       function( other.function),
       pos (other.pos),
       dir ( other.dir),
       radius ( other.radius),
       penumbra ( other.penumbra),
       angle ( other.angle),
       width (other.width),
       height ( other.height)
   {

   }

   CS123SceneLightData(CS123SceneLightData& other):
       id (other.id),
       type( other.type),
       color(other.color),
       function( other.function),
       pos (other.pos),
       dir ( other.dir),
       radius ( other.radius),
       penumbra ( other.penumbra),
       angle ( other.angle),
       width (other.width),
       height ( other.height)
   {

   }

   void operator=(const CS123SceneLightData& other){
       id = other.id;
       type = other.type;
       color = other.color;
       function = other.function;
       pos = other.pos;
       dir = other.dir;
       radius = other.radius;
       penumbra = other.penumbra;
       angle = other.angle;
       width = other.width;
       height = other.height;
   }

   void operator=(CS123SceneLightData& other)
   {
     id = other.id;
     type = other.type;
     color = other.color;
     function = other.function;
     pos = other.pos;
     dir = other.dir;
     radius = other.radius;
     penumbra = other.penumbra;
     angle = other.angle;
     width = other.width;
     height = other.height;
   }
};

// Data for scene camera
struct CS123SceneCameraData {
   glm::vec4 pos;
   glm::vec4 look;
   glm::vec4 up;

   float heightAngle;
   float aspectRatio;

   float aperture;      // Only applicable for depth of field
   float focalLength;   // Only applicable for depth of field
};

// Data for file maps (ie: texture maps)
struct CS123SceneFileMap {
//    CS123SceneFileMap() : texid(0) {}
   bool isUsed;
   std::string filename;
   float repeatU;
   float repeatV;

   CS123SceneFileMap(){}


   CS123SceneFileMap(CS123SceneFileMap& other):filename(other.filename),
       isUsed(other.isUsed),
       repeatU(other.repeatU),
       repeatV(other.repeatV)
   {

   };

   CS123SceneFileMap(const CS123SceneFileMap& other):
       isUsed(other.isUsed),
       filename(other.filename),
       repeatU(other.repeatU),
       repeatV(other.repeatV)
   {

   };

   void clear() {
       isUsed = false;
       repeatU = 0.0f;
       repeatV = 0.0f;
       filename = std::string();
   }
};

// Data for scene materials
struct CS123SceneMaterial {
   // This field specifies the diffuse color of the object. This is the color you need to use for
   // the object in sceneview. You can get away with ignoring the other color values until
   // intersect and ray.
//   CS123SceneMaterial() {}
   CS123SceneColor cDiffuse;
   
   CS123SceneColor cAmbient;
   CS123SceneColor cReflective;
   CS123SceneColor cSpecular;
   CS123SceneColor cTransparent;
   CS123SceneColor cEmissive;

   CS123SceneFileMap textureMap;
   float blend;

   CS123SceneFileMap bumpMap;

   float shininess;

   float ior; // index of refraction

   void clear() {
       cAmbient.r = 0.0f; cAmbient.g = 0.0f; cAmbient.b = 0.0f; cAmbient.a = 0.0f;
       cDiffuse.r = 0.0f; cDiffuse.g = 0.0f; cDiffuse.b = 0.0f; cDiffuse.a = 0.0f;
       cSpecular.r = 0.0f; cSpecular.g = 0.0f; cSpecular.b = 0.0f; cSpecular.a = 0.0f;
       cReflective.r = 0.0f; cReflective.g = 0.0f; cReflective.b = 0.0f; cReflective.a = 0.0f;
       cTransparent.r = 0.0f; cTransparent.g = 0.0f; cTransparent.b = 0.0f; cTransparent.a = 0.0f;
       cEmissive.r = 0.0f; cEmissive.g = 0.0f; cEmissive.b = 0.0f; cEmissive.a = 0.0f;
       textureMap.clear();
       bumpMap.clear();
       blend = 0.0f;
       shininess = 0.0f;
       ior = 0.0;
   }

   CS123SceneMaterial():cDiffuse(CS123SceneColor(0,0,0,0)),cAmbient(CS123SceneColor(0,0,0,0)),
   cReflective(CS123SceneColor(0,0,0,0)),cSpecular(CS123SceneColor(0,0,0,0)),cTransparent(CS123SceneColor(0,0,0,0)),
     cEmissive(CS123SceneColor(0,0,0,0)),textureMap(),blend(0.0)
   {

   }

   CS123SceneMaterial(const CS123SceneMaterial& other):cDiffuse(other.cDiffuse),cAmbient(other.cAmbient),
       cReflective(other.cReflective),cSpecular(other.cSpecular),cTransparent(other.cTransparent),cEmissive(other.cEmissive),
       textureMap(other.textureMap),shininess(other.shininess),blend(other.blend)
   {

   }

   CS123SceneMaterial(CS123SceneMaterial& other):cDiffuse(other.cDiffuse),cAmbient(other.cAmbient),
       cReflective(other.cReflective),cSpecular(other.cSpecular),cTransparent(other.cTransparent),cEmissive(other.cEmissive),
       textureMap(other.textureMap),shininess(other.shininess),blend(other.blend)
   {

   }


    void operator=(CS123SceneMaterial& other)
   {
        cDiffuse = other.cDiffuse;
        cAmbient =other.cAmbient;
        cReflective = other.cReflective;
        cSpecular=other.cSpecular;
        cTransparent=other.cTransparent;
        cEmissive = (other.cEmissive);
        textureMap = other.textureMap;
        shininess = other.shininess;
        blend = other.blend;
   }

    void operator=(const CS123SceneMaterial& other)
   {
        cDiffuse = other.cDiffuse;
        cAmbient =other.cAmbient;
        cReflective = other.cReflective;
        cSpecular=other.cSpecular;
        cTransparent=other.cTransparent;
        cEmissive = (other.cEmissive);
        textureMap = other.textureMap;
        shininess = other.shininess;
   }
};

struct CS123ScenePrimitive {
   PrimitiveType type;
   std::string meshfile;     // Only applicable to meshes
   CS123SceneMaterial material;
};

// Data for transforming a scene object. Aside from the TransformationType, the remaining of the
// data in the struct is mutually exclusive.
struct CS123SceneTransformation {
    TransformationType type;

    glm::vec3 translate; // The translation vector. Only valid if transformation is a translation.
    glm::vec3 scale;     // The scale vector. Only valid if transformation is a scale.
    glm::vec3 rotate;    // The axis of rotation. Only valid if the transformation is a rotation.
    float angle;         // The rotation angle in RADIANS. Only valid if transformation is a
                         // rotation.

    glm::mat4x4 matrix;  // The matrix for the transformation. Only valid if the transformation is
                         // a custom matrix.
};

// Structure for non-primitive scene objects
struct CS123SceneNode {
   std::vector<CS123SceneTransformation*> transformations;

   std::vector<CS123ScenePrimitive*> primitives;

   std::vector<CS123SceneNode*> children;
};

#endif

