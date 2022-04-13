//
//  Programa.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//
#define GL_SILENCE_DEPRECATION
#ifndef Programa_hpp
#define Programa_hpp

#include "ImGuiMy.hpp"
#include "InputListener.hpp"
#include "Shader.hpp"

#include "FileManager.hpp"
#include "ECS/ECSManager.hpp"
#include "ECS/Component.hpp"
#include "ECS/Components/Model.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/PointLightComponent.hpp"
#include "ECS/Components/SpotLightComponent.hpp"
#include "ECS/Components/DirectionalLightComponent.hpp"
#include "ECS/Components/TagName.hpp"
#include "ECS/Systems/Render.hpp"


//Game
#include "ECS/Components/Game/WeaponComponent.hpp"
#include "ECS/Components/Game/ProjectileComponent.hpp"
#include "ECS/Systems/Game/Weapon.hpp"
#include "ECS/Systems/Game/Projectile.hpp"


class Programa
{
public:
    
    Programa();
    ~Programa(){};
    
    void run();
    void exit();

    static void resizeWindow(GLFWwindow* window2, int width, int height) {
        glViewport(0, 0, width, height);
        _instance->Width = width;
        _instance->Height = height;
//        _Instancia->_ImGui->update();  updatear los sie para Imgui.
    }

private:
    
    void init();
    void loop();
    void initECS();
    void loadShaders();
    
    static Programa* _instance;
    GLFWwindow* _window;
    uint32_t Width;
    uint32_t Height;
    std::string _title;
    Shader shader;
    std::unique_ptr<ECSManager> _ECSManager;
    std::unique_ptr<ImGuiMy> _imGui;
    std::unique_ptr<FileManager> _fileManager;
    std::shared_ptr<InputListener> _inputListener;
    Camera camera = Camera(60.0f, 1280, 720, 0.1f, 1000.0f, glm::vec3(10.0f, 3.0f, 10.0f));
    
    std::shared_ptr<Render> renderSystem;
    std::shared_ptr<Weapon> weaponSystem;
    std::shared_ptr<Projectile> projectileSystem;
    std::vector<GameObject> gameObjects;
    

    float lastFrame = 0.0f;
    float deltaTime = 0.0f;
    
    bool gameMode = false;
    
    unsigned int shaderProgram;
    std::vector<uint32_t> shaders;
};


#endif /* Programa_hpp */
