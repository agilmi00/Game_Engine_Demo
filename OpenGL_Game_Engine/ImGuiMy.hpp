//
//  ImGui.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef ImGuiMy_hpp
#define ImGuiMy_hpp

#include <stdio.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include "Vendor/ImGui/imgui.h"
#include "Vendor/ImGui/imgui_impl_glfw.h"
#include "Vendor/ImGui/imgui_impl_opengl3.h"
#include "Vendor/ImGuizmo/ImGuizmo.h"


#include "GameObjectManager.hpp"
#include "TransformComponent.hpp"

#include "TagName.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include "FileManager.hpp"
#include "Vendor/FileDialog/portable-file-dialogs.h"

#include "WeaponComponent.hpp"

#define DEFAULT_PATH "Assets"

class Programa;

class ImGuiMy
{
    
public:
    ImGuiMy(GLFWwindow* window, Camera* camera, std::unique_ptr<FileManager> & fileManager, Programa* Prog)
    {
        _window = window;
        _camera = camera;
        _fileManager = fileManager.get();
        
        _prog = Prog;
    }
    ~ImGuiMy()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
    }
    
    void initImGui(std::vector<GameObject>& gameObjects);
    void setECSManager(std::unique_ptr<ECSManager>& ECSManager);
    void update();
private:
    
    Programa* _prog;
    ECSManager* _ECSManager;
    GLFWwindow* _window;
    void initDockspace();
    void initSceneHierarchy();
    void initGuizmo();
    void components();
    void dragFloat(const std::string& label, float& value, float columWidth, float dragMaxValue);
    void vec3Drag(const std::string& label, glm::vec3& values, float resetValue, float columWidth);
    GameObject gameObjectSelected;
    std::vector<GameObject>* _gameObjects;
    Info info;
    Camera* _camera;
    FileManager* _fileManager;
    bool selected = false;  
    
};
#endif /* ImGuiMy_hpp */
