//
//  Programa.cpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#include "Programa.hpp"
#include "ImGuiMy.hpp"
Programa* Programa::_instance = nullptr;

Programa::Programa()
{
    _instance = this;
    Width = 1280;
    Height = 720;
    _title = "OpenGL Game Engine";
    
}
void Programa::run()
{
    try{
        init();
    }
    catch (std::exception &exception)
    {
        std::cerr << exception.what() << std::endl;
    }
}
void Programa::init()
{
    
    // Initialize GLFW
    if (!glfwInit())
    {
        throw ("ERROR: Can't initialize GLFW");
    }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Create the window
    _window = glfwCreateWindow(Width, Height, _title.c_str(), NULL, NULL);
    if (_window == NULL)
    {
        throw ("ERROR: Can't create GLFW window");
    }
    glfwMakeContextCurrent(_window);
    
    // Configure global opengl state
    glEnable(GL_DEPTH_TEST);
    glfwSetWindowSizeCallback(_window, resizeWindow);
    
    loadShaders();
    
    initECS();
    _inputListener = std::make_shared<InputListener>(_window, &camera, _ECSManager, gameObjects, &gameMode);
//    _ImGui = new ImGuiMy(_window, &camera);
//    _imGui->initImGui(gameObjects);
    _fileManager = std::make_unique<FileManager>(_ECSManager);
    _imGui = std::make_unique<ImGuiMy>(_window, &camera, _fileManager, this);
    _imGui->initImGui(gameObjects);
    _imGui->setECSManager(_ECSManager);
    loop();
    
}
void Programa::initECS()
{
    _ECSManager = std::make_unique<ECSManager>();
    _ECSManager->init();
    
    _ECSManager->newComponent<TagName>();
    _ECSManager->newComponent<TransformComponent>();
    _ECSManager->newComponent<Model>();
    
    
    // System register
    renderSystem = _ECSManager->newSystem<Render>();
    {
        Info info;
        info.set(_ECSManager->getComponentType<Model>());
        info.set(_ECSManager->getComponentType<TransformComponent>());
        _ECSManager->setSystemInfo<Render>(info);
        _ECSManager->newComponent<DirectionalLightComponent>();
        _ECSManager->newComponent<PointLightComponent>();
        _ECSManager->newComponent<SpotLightComponent>();
        
    }
    renderSystem->init(&camera, shaders[0], _ECSManager);
    
    //Game
    _ECSManager->newComponent<WeaponComponent>();
    _ECSManager->newComponent<ProjectileComponent>();
    weaponSystem = _ECSManager->newSystem<Weapon>();
    {
        Info info;
        info.set(_ECSManager->getComponentType<WeaponComponent>());
        info.set(_ECSManager->getComponentType<TransformComponent>());
        _ECSManager->setSystemInfo<Weapon>(info);
    }
    weaponSystem->init(&camera, _ECSManager);
    
    projectileSystem = _ECSManager->newSystem<Projectile>();
    {
        Info info;
        info.set(_ECSManager->getComponentType<ProjectileComponent>());
        info.set(_ECSManager->getComponentType<TransformComponent>());
        _ECSManager->setSystemInfo<Projectile>(info);
    }
    projectileSystem->init(_ECSManager);
    
}
void Programa::exit()
{
    for (auto& gameObject : gameObjects)
    {
        auto& model = _ECSManager->getComponent<Model>(gameObject);
        model.modelo.freeVram();
    }
    _ECSManager.reset();
    gameObjects.clear();
    initECS();
    _imGui->setECSManager(_ECSManager);
    _fileManager->setECSManager(_ECSManager);
    
    
}

void Programa::loadShaders()
{
    shader = Shader();
    shaderProgram = shader.setUp("Assets/Shaders/vertexShader.vs", "Assets/Shaders/fragmentShader.fs");
    shaders.push_back(shaderProgram);
}

void Programa::loop()
{
    
    while (!glfwWindowShouldClose(_window))
    {
        float frame = glfwGetTime();
        deltaTime = frame - lastFrame;
        lastFrame = frame;
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        _inputListener->keyboard(deltaTime);
        _inputListener->mouseInput(deltaTime);
        renderSystem->update();
        weaponSystem->update(deltaTime);
        projectileSystem->update(deltaTime);
        if (!gameMode) {
            _imGui->update();
        }
        glfwPollEvents();
        glfwSwapBuffers(_window);
    }
    glfwTerminate();
}
