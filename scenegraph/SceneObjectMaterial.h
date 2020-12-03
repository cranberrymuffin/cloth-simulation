#ifndef SCENEOBJECTMATERIAL_H
#define SCENEOBJECTMATERIAL_H

#include "../lib/CS123SceneData.h"
#include <gl/textures/Texture2D.h>
#include "gl/textures/TextureParametersBuilder.h"
#include "gl/textures/TextureParameters.h"
#include <memory>
#include <QImage>

class RGBA;
class SceneObject;
typedef CS123SceneMaterial Material;

class SceneObjectMaterial
{
public:
    SceneObjectMaterial();
    SceneObjectMaterial(SceneObject* parent, const Material& m);
    SceneObjectMaterial(SceneObjectMaterial& m);
    void operator=(SceneObjectMaterial& m);

    ~SceneObjectMaterial();

    Material& getMaterial();


   QImage& getTexture();
   void setMaterial(Material& material);

   int textureWidth();
   int textureHeight();

   glm::vec4 getTextureColor(const glm::vec2& position);
   RGBA getTextelAt(int s, int t );

private:
    Material m_material;
    std::unique_ptr<QImage> m_texture;
    int m_textureHeight;
    int m_textureWidth;
    SceneObject* m_objectParent;
    RGBA * data;
};

#endif // SCENEOBJECTMATERIAL_H
