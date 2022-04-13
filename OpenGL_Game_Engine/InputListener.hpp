//
//  InputListener.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef InputListener_hpp
#define InputListener_hpp


#include <stdio.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include <GLFW/glfw3.h>
#include "Camera.hpp"
#include "ECS/ECSManager.hpp"

#include "TagName.hpp"
#include "Model.hpp"
#include "TransformComponent.hpp"
#include "ProjectileComponent.hpp"

class InputListener
{
public:
    InputListener(GLFWwindow* window, Camera* camera, std::unique_ptr<ECSManager> & ECSManager, std::vector<GameObject>& gameObjects, bool* gameMode);
    ~InputListener(){}
    
    void keyboard(float &deltaTime);
    static void mouseMovement(GLFWwindow *window, double posX, double posY);
    static void mouseNoMovement(GLFWwindow *window, double posX, double posY);
    void mouseInput(float &deltaTime);
    void fire();
    

private:
    GLFWwindow* _window;
    Camera* _camera;
    ECSManager* _ECSManager;
    std::vector<GameObject>* _gameObjects;
    static InputListener* _instance;
    //Mouse & Keyboard
    bool ratonInicial = true;
    bool invertedY = false;
    bool mouseMove = false;
    float yaw   = -90.0f;    // Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    float pitch =  0.0f;    // Get all of this from camera getters.
    float lastX =  1280 / 2.0; // Width camera / 2
    float lastY =  720 / 2.0;
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;
    float shootCooldown = 0.5f;
    float shootCooldownT = shootCooldown;
    float inputLag = 0.5f;
    std::shared_ptr<Modelo> projectile;
    
    bool* _gameMode;
    glm::vec3 camFront;
};
#endif /* InputListener_hpp */
