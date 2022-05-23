//
//  InputListener.cpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#include "InputListener.hpp"

InputListener* InputListener::_instance = nullptr;

InputListener::InputListener(GLFWwindow* window, Camera* camera, std::unique_ptr<ECSManager> & ECSManager, std::vector<GameObject>& gameObjects, bool* gameMode)
{
    _instance = this;
    _window = window;
    _camera = camera;
    _ECSManager = ECSManager.get();
    _gameObjects = &gameObjects;
    _gameMode = gameMode;
    glfwSetCursorPosCallback(_window, _instance->mouseNoMovement);
    std::string ruta = "/Users/Cl0ud7/Documents/XCode Projects/OpenGL_Game_Engine/OpenGL_Game_Engine/Assets/Modelos/Caja/Caja.obj";
    projectile = std::make_shared<Modelo>(ruta);
}

void InputListener::keyboard(float& deltaTime)
{
//    float frame = glfwGetTime();
//    deltaTime = frame - lastFrame;
//    lastFrame = frame;
    
    inputLag -= deltaTime;
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(_window, true);
    }
    if (glfwGetKey(_window, GLFW_KEY_0) == GLFW_PRESS && inputLag < 0.0f)
    {
        if(!*_gameMode)
        {
            *_gameMode = true;
            _camera->position = glm::vec3(10.0f, 3.0f, 10.0f);
            glfwSetCursorPosCallback(_window, _instance->mouseMovement);
            glfwSetInputMode(_window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
            mouseMove = true;
        }
        else
        {
            *_gameMode = false;
            glfwSetCursorPosCallback(_window, _instance->mouseNoMovement);
            glfwSetInputMode(_window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
            mouseMove = false;
        }
        inputLag = 0.5f;
    }
    float velocidadCamera = 10.0f * deltaTime;
    
    if (!*_gameMode)
    {
        if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
        {
            _camera->position += velocidadCamera * _camera->getCameraFront();
        }
        if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
        {
            _camera->position -= velocidadCamera * _camera->getCameraFront();
        }
    }
    else
    {
        // First person GameCam
        camFront = glm::normalize(glm::vec3(1,0,1) * _camera->getCameraFront());

        if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
            _camera->position += (velocidadCamera * camFront);
        if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
            _camera->position -= (velocidadCamera * camFront);
    }
    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        _camera->position -= glm::normalize(glm::cross(_camera->getCameraFront(), _camera->getCameraUp())) * velocidadCamera;
    }
    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        _camera->position += glm::normalize(glm::cross(_camera->getCameraFront(), _camera->getCameraUp())) * velocidadCamera;
    }
    
    
    // Center the mouse
    if (glfwGetKey(_instance->_window, GLFW_KEY_SPACE) == GLFW_PRESS && inputLag < 0.0f)
    {
        
        if (!mouseMove)
        {
            glfwSetCursorPosCallback(_window, _instance->mouseMovement);
            glfwSetInputMode(_window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
            mouseMove = true;
        }
        else
        {
            glfwSetCursorPosCallback(_window, _instance->mouseNoMovement);
            glfwSetInputMode(_window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
            mouseMove = false;
        }
        _instance->lastX = 1280 / 2.0;
        _instance->lastY = 720 / 2.0;
        inputLag = 0.5f;
    }
}
void InputListener::mouseNoMovement(GLFWwindow *window, double posX, double posY)
{
    
}
void InputListener::mouseMovement(GLFWwindow *window, double posX, double posY)
{
    
        if (_instance->ratonInicial)
        {
            _instance->lastX = posX;
            _instance->lastY = posY;
            _instance->ratonInicial = false;
        }

        float offsetX = posX - _instance->lastX;
        float offsetY;
        if (_instance->invertedY) {
            offsetY = posY - _instance->lastY;
        }
        else {
            offsetY = _instance->lastY - posY;
        }

        _instance->lastX = posX;
        _instance->lastY = posY;

        float sensibilidad = 0.1f;
        offsetX *= sensibilidad;
        offsetY *= sensibilidad;

        _instance->yaw += offsetX;
        _instance->pitch += offsetY;


        if (_instance->pitch > 90.0f)
            _instance->pitch = 90.0f;
        if (_instance->pitch < -90.0f)
            _instance->pitch = -90.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(_instance->yaw)) * cos(glm::radians(_instance->pitch));
        front.y = sin(glm::radians(_instance->pitch));
        front.z = sin(glm::radians(_instance->yaw)) * cos(glm::radians(_instance->pitch));
        _instance->_camera->setCameraFront(glm::normalize(front));
//        glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
      
    
}
void InputListener::mouseInput(float& deltaTime)
{
    shootCooldownT -= deltaTime;
//    std::cout << shootCooldownT;
    if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && shootCooldownT < 0.0f)
    {
        fire();
    }
}
void InputListener::fire()
{
//    _camera->position += velocidadCamera * _camera->getCameraFront();
    glm::vec3 camPos = _camera->position;
    camPos += _camera->getCameraFront() * 8.0f;
//    camPos.z -= 10;
    GameObject gameObject;
    gameObject = _ECSManager->createGameObject();
    _ECSManager->addComponent(gameObject, TagName{.tagName = std::to_string(gameObject)});
    _ECSManager->addComponent(gameObject, Model{.modelo = *projectile});
    _ECSManager->addComponent(gameObject, ProjectileComponent{.direction = _camera->getCameraFront(),.shootPosition = camPos});
    _ECSManager->addComponent(gameObject, TransformComponent{.Translation = camPos});
//    ECSManager->getComponent<TransformComponent>(gameObject).Translation = _camera->position;
    
//    _gameObjects->push_back(gameObject);
    shootCooldownT = shootCooldown;
    
    
}
