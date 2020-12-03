#include "SceneObjectMaterial.h"

#include <QGLWidget>
#include <QImage>
#include "lib/RGBA.h"
#include "scenegraph/SceneObject.h"

SceneObjectMaterial::SceneObjectMaterial():m_texture(nullptr),m_objectParent(nullptr),
    m_textureHeight(-1),m_textureWidth(-1),data(nullptr)
{
  m_texture = std::make_unique<QImage>(1, 1, QImage::Format_RGBX8888);

}

SceneObjectMaterial::SceneObjectMaterial(SceneObject* parent,const Material& material):
    m_material(material)
  ,m_objectParent(parent)
  ,data(nullptr)
{

    m_texture = std::make_unique<QImage>(QString::fromStdString(m_material.textureMap.filename));
    if(m_material.textureMap.isUsed)
    {

        QImage *temp = new QImage();

       if(temp->load(m_material.textureMap.filename.data()))
      //  if(m_texture)
       {
           m_textureWidth = temp->width();
           m_textureHeight = temp->height();
           if (temp->format() != QImage::Format_RGBX8888) {
               QImage* old = temp;
               temp = new QImage(old->convertToFormat(QImage::Format_RGBX8888));
               delete old;
           }


          data = new RGBA[m_textureWidth*m_textureHeight] ;
          memcpy(data,reinterpret_cast<RGBA *>(temp->bits()), temp->sizeInBytes());
       }
       else{
           m_material.textureMap.isUsed = false;
       }
       delete temp;
    }



//      texture =  std::make_unique<CS123::GL::Texture2D>(fImage.bits(), fImage.width(), fImage.height());
//      CS123::GL::TextureParametersBuilder builder;
//      builder.setFilter(CS123::GL::TextureParameters::FILTER_METHOD::LINEAR);
//      builder.setWrap(CS123::GL::TextureParameters::WRAP_METHOD::REPEAT);
//      CS123::GL::TextureParameters parameters = builder.build();
//      parameters.applyTo(*texture.get());

}

SceneObjectMaterial::SceneObjectMaterial(SceneObjectMaterial &other):
    m_material(other.m_material),
    m_objectParent(other.m_objectParent),
   data(nullptr)
{
    m_texture = std::make_unique<QImage>(QString::fromStdString(m_material.textureMap.filename));
    if(m_material.textureMap.isUsed)
    {

        QImage *temp = new QImage();

       if(temp->load(m_material.textureMap.filename.data()))
       // if(m_texture)
       {
           m_textureWidth = temp->width();
           m_textureHeight = temp->height();
           if (temp->format() != QImage::Format_RGBX8888) {
               QImage* old = temp;
               temp = new QImage(old->convertToFormat(QImage::Format_RGBX8888));
               delete old;
           }


          data = new RGBA[m_textureWidth*m_textureHeight] ;
          memcpy(data,reinterpret_cast<RGBA *>(temp->bits()), temp->sizeInBytes());
       }
       else{
           m_material.textureMap.isUsed = false;
       }
       delete temp;
    }
}

void SceneObjectMaterial::operator=(SceneObjectMaterial &other)
{
    m_material = other.m_material;
    m_objectParent = other.m_objectParent;
    data = other.data;
}

SceneObjectMaterial::~SceneObjectMaterial()
{
    std::cout << "~SceneObjectMaterial()" << std::endl;
    if(data)
    {
        delete data;
    }

}

Material& SceneObjectMaterial::getMaterial()
{
    return m_material;
}

QImage& SceneObjectMaterial::getTexture()
{
    return *m_texture.get();
}

void SceneObjectMaterial::setMaterial(Material &material)
{
    m_material = material;
}

int SceneObjectMaterial::textureWidth()
{
    return m_textureWidth;
}

int SceneObjectMaterial::textureHeight()
{
     return m_textureHeight;
}

glm::vec4 SceneObjectMaterial::getTextureColor(const glm::vec2& uv)
{

   int s =  (int)(uv.x*m_material.textureMap.repeatU*m_textureWidth)
           %m_textureWidth;

   int t =  (int)((1-uv.y)*m_material.textureMap.repeatV*m_textureHeight)
           %m_textureHeight;


   RGBA textColor = data[t*m_textureWidth+s];

   // no idea why I am doing it like this
   glm::vec4 rgbaText(textColor.r,textColor.g,textColor.b,textColor.a);

   return rgbaText/255.f;


}

RGBA SceneObjectMaterial::getTextelAt(int s, int t)
{
   RGBA textel = data[t*m_textureWidth+s] ;
   return textel;
}
