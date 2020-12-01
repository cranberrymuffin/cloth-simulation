/**
 * @file   CamtransCamera.cpp
 *
 * This is the perspective camera class you will need to fill in for the Camtrans lab.  See the
 * lab handout for more details.
 */

#include "CamtransCamera.h"
#include <Settings.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

CamtransCamera::CamtransCamera():m_near(0.0),m_far(100.0),m_thetaH(60.0),m_aspectRatio(1.0),
    m_eye(2.0,2.0,2.0,0.0),m_look(-2.0,-2.0,-2.0,0.0),m_up(0.0,1.0,0.0,0.0)
{
    // @TODO: [CAMTRANS] Fill this in...
    orientLook(m_eye,m_look,m_up);

}

void CamtransCamera::setAspectRatio(float a)
{
   // std::cout << "setAspectRatio: " << a << std::endl;
    // @TODO: [CAMTRANS] Fill this in...
    m_aspectRatio = a;
    updateProjectionMatrix();
}

glm::mat4x4 CamtransCamera::getProjectionMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...

    return  m_perspectiveTransformation * m_scaleMatrix  ;
}

glm::mat4x4 CamtransCamera::getViewMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...

    return    m_rotationMatrix*m_translationMatrix ;
}

glm::mat4x4 CamtransCamera::getScaleMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_scaleMatrix;
}

glm::mat4x4 CamtransCamera::getPerspectiveMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...

    return m_perspectiveTransformation;
}

glm::vec4 CamtransCamera::getPosition() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_eye;
}

glm::vec4 CamtransCamera::getLook() const {
    // @TODO: [CAMTRANS] Fill this in...
    return -m_w;
}

glm::vec4 CamtransCamera::getUp() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_up;
}

float CamtransCamera::getAspectRatio() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_aspectRatio;
}

float CamtransCamera::getHeightAngle() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_thetaH;
}

void CamtransCamera::orientLook(const glm::vec4 &eye, const glm::vec4 &look, const glm::vec4 &up) {
    // @TODO: [CAMTRANS] Fill this in...

   std::cout << "trasnlate " << eye.x <<"," << eye.y <<","<< eye.z << std::endl;
   std::cout << "trasnlate " << look.x <<"," << look.y <<","<< look.z << std::endl;
   std::cout << "trasnlate " << up.x <<"," << up.y <<","<< up.z << std::endl;

    m_eye = eye;
    //m_look = look;
    m_up = up;

    m_w = glm::normalize(-look);
    m_v = glm::normalize(m_up - glm::dot(m_up,m_w) * m_w);
    m_u = glm::vec4(glm::cross(m_v.xyz(),m_w.xyz()),0.0);

    updateViewMatrix();
    updateProjectionMatrix();

}

void CamtransCamera::setHeightAngle(float h) {

//    std::cout << "setHeightAngle "<< h<< std::endl;
//    // @TODO: [CAMTRANS] Fill this in...
    m_thetaH = h;
    updateProjectionMatrix();
}

void CamtransCamera::translate(const glm::vec4 &v) {
    // @TODO: [CAMTRANS] Fill this in...
    std::cout << "trasnlate " << v.x <<"," << v.y <<","<< v.z << std::endl;
    m_eye +=  v;
    updateViewMatrix();
}

void CamtransCamera::rotateU(float degrees) {
    // @TODO: [CAMTRANS] Fill this in...
    float rad = glm::radians(degrees);
    glm::vec4 tmp = glm::cos(rad)*m_v + glm::sin(rad)*m_w;
    m_w = -glm::sin(rad)*m_v + glm::cos(rad)*m_w;
    m_v = tmp;

   updateViewMatrix();
}

void CamtransCamera::rotateV(float degrees) {
    // @TODO: [CAMTRANS] Fill this in...
    float rad = glm::radians(degrees);
       glm::vec4 tmp = glm::cos(rad)*m_w + glm::sin(rad)*m_u;
       m_u = -glm::sin(rad)*m_w + glm::cos(rad)*m_u;
       m_w = tmp;
        updateViewMatrix();
}

void CamtransCamera::rotateW(float degrees) {
    // @TODO: [CAMTRANS] Fill this in...
    float rad = glm::radians(degrees);
       glm::vec4 tmp = glm::cos(rad)*m_u + glm::sin(rad)*m_v;
       m_v = -glm::sin(rad)*m_u + glm::cos(rad)*m_v;
       m_u = tmp;
        updateViewMatrix();
}

void CamtransCamera::setClip(float nearPlane, float farPlane) {
    // @TODO: [CAMTRANS] Fill this in...
//    std::cout << "setClip : near :" << nearPlane <<" far: " <<farPlane << std::endl;
    m_near = nearPlane;
    m_far = farPlane;
   updateProjectionMatrix();
}

void CamtransCamera::updateProjectionMatrix()
{
    updateScaleMatrix();
    updatePerspectiveMatrix();
}

void CamtransCamera::updatePerspectiveMatrix()
{
   // updateScaleMatrix();
    float c = -m_near/m_far;
    glm::mat4 Mpp = glm::mat4(glm::vec4(1.0,0.0,0.0,0.0),
                         glm::vec4(0.0,1.0,0.0,0.0),
                         glm::vec4(0.0,0.0,-1.f/(1.f+c),-1.0),
                         glm::vec4(0.0,0.0,c/(1.f+c),0.0));
    m_perspectiveTransformation =  Mpp; //  is the projection not the perspective
}

void CamtransCamera::updateScaleMatrix()
{

  //float f = glm::length(m_far - m_eye);


  float heigthAngle =m_far * glm::tan(glm::radians(m_thetaH) * 0.5f);
  float widthAngle = m_aspectRatio * heigthAngle;

  m_scaleMatrix = glm::scale(glm::vec3(1.f/widthAngle,1.f/heigthAngle,1.f/m_far));

}

void CamtransCamera::updateViewMatrix()
{
    updateTranslationMatrix();
    updateRotationMatrix();

}

void CamtransCamera::updateRotationMatrix()
{


    m_rotationMatrix =  glm::transpose(glm::mat4(m_u,m_v,m_w,glm::vec4(0.0,0.0,0.0,1.0)));


}

void CamtransCamera::updateTranslationMatrix()
{
   //glm::vec4 P = glm::vec4(m_eye.xyz() - (m_near * m_w.xyz()),1.0);
   m_translationMatrix = glm::translate(glm::mat4(1),-m_eye.xyz());


}

glm::vec4 CamtransCamera::getU() const
{
  return m_u;
}

glm::vec4 CamtransCamera::getV() const
{
 return m_v;
}

glm::vec4 CamtransCamera::getW() const
{
return m_w;
}

