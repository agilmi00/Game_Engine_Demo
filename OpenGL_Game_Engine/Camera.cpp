//
//  Camera.cpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#include "Camera.hpp"

Camera::Camera(GLfloat FOV, GLfloat width, GLfloat height, GLfloat nearPlane, GLfloat farPlane, glm::vec3 camPosition)
{
    position = camPosition;
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    viewMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::mat4(1.0f);
    viewMatrix = glm::lookAt(position, position + cameraFront, cameraUp);
    projectionMatrix = glm::perspective(glm::radians(FOV), width / height, nearPlane, farPlane);
//    projectionMatrix = glm::ortho(0.0f, width, 0.0f, height, nearPlane, farPlane);
}
mth::Matrix4 Camera::model(const mth::Vector3& translation, const mth::Quatern& rotation, const mth::Vector3& scale)
{
    return (mth::translate(mth::Matrix4(1.0f), translation) *  mth::RotationM4(rotation) * mth::scale(mth::Matrix4(1.0f), scale));
}

glm::mat4 Camera::getView()
{
    //    View Matrix - > World to View Space
    viewMatrix = glm::lookAt(position, position + cameraFront, cameraUp);
    return viewMatrix;
}

glm::mat4 Camera::getProjection()
{
    
    //    Projection Matrix - > View to Clip Space
    return projectionMatrix;
}
glm::vec3 Camera::getCameraFront()
{
    
    return cameraFront;
}
glm::vec3 Camera::getCameraUp()
{
    
    return cameraUp;
}
void Camera::setCameraFront(glm::vec3 front)
{
    cameraFront = front;
}
