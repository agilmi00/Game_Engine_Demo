//
//  Camera.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include <iostream>


#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/matrix_decompose.hpp"


class Camera {

public:
    Camera(GLfloat FOV, GLfloat width, GLfloat height, GLfloat nearPlane, GLfloat farPlane, glm::vec3 camPos);
    ~Camera(){};
    
    glm::vec3 position;
    static glm::mat4 model(glm::vec3 translation, glm::vec3 rotacion, glm::vec3 Scale);
    glm::mat4 rotationMatrix(glm::vec3 rotation);
    glm::mat4 getView();
    glm::mat4 getProjection();
    glm::vec3 getCameraFront();
    glm::vec3 getCameraUp();
    void setCameraFront(glm::vec3 front);
    
private:
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
};

#endif /* Camera_hpp */
