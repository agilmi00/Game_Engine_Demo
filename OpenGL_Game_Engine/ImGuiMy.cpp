//
//  ImGui.cpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//


#include "Programa.hpp"

void ImGuiMy::initImGui(std::vector<GameObject>& gameObjects)
{
    ImGui::CreateContext();
    
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    
    ImGui::StyleColorsDark();
    
    
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
    _gameObjects = &gameObjects;
    _fileManager->init(gameObjects);
    
}
void ImGuiMy::setECSManager(std::unique_ptr<ECSManager> & ECSManager)
{
    _ECSManager = ECSManager.get();
}

void ImGuiMy::update()
{
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(1280.0f, 720.0f);
    
    ImGui::NewFrame();
    ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
    ImGuizmo::BeginFrame();
    
    initDockspace();

    // Scene hierarchy
    initSceneHierarchy();
    
    //Gizmo
    initGuizmo();

    ImGui::End();
    ImGui::Render();
    
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void ImGuiMy::initDockspace()
{
    static bool dockspaceOpen = true;
    
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGuiWindowFlags host_window_flags = 0;
    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
    
    host_window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking;
    host_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoNavFocus;
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) {
                    host_window_flags |= ImGuiWindowFlags_NoBackground;
    }
    ImGui::Begin("Dockspace", &dockspaceOpen, host_window_flags);

    // Dockspace
    ImGui::DockSpace(ImGui::GetID("Dockspace"), ImVec2(0.0f, 0.0f), dockspace_flags, nullptr);
         
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {

            if (ImGui::MenuItem("New", "Ctrl+N"))
            {
                _prog->exit();
                selected = false;
            }
            if (ImGui::MenuItem("Open"))
            {
                _fileManager->deserialize("Scene.json");
            }
            if (ImGui::MenuItem("Save"))
            {
                _fileManager->serialize("Scene.json");
            }
            ImGui::EndMenu();
        }
        ImGui::Text("Frametime %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::EndMenuBar();
    }
}

void ImGuiMy::initSceneHierarchy()
{
    
    ImGui::Begin("Scene hierarchy");
    ImGui::PushStyleColor(ImGuiCol_Button,  ImVec4{ 0.0f, 0.7f, 0.15f, 1.0f });
    if(ImGui::Button("New GameObject"))
    {
        GameObject gameObject;
        gameObject = _ECSManager->createGameObject();
        _ECSManager->addComponent(gameObject, TagName{.tagName = std::to_string(gameObject)});
        _gameObjects->push_back(gameObject);
        gameObjectSelected = gameObject;
        info = _ECSManager->getInfoGameObject(gameObjectSelected);
        selected = true;
    }
    ImGui::PopStyleColor(1);
    ImGui::PushStyleColor(ImGuiCol_Button,  ImVec4{ 0.7f, 0.0f, 0.15f, 1.0f });
    if(ImGui::Button("Delete"))
    {
        _ECSManager->removeGameObject(gameObjectSelected);
//        _gameObjects->erase(gameObjectSelected);
    }
    ImGui::PopStyleColor(1);
    for (GameObject gameObject : *_gameObjects)
    {
        if (gameObject == gameObjectSelected)
        {
            ImGui::PushStyleColor(ImGuiCol_Button,  ImVec4{ 0.0f, 0.5f, 0.15f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered,  ImVec4{ 0.0f, 0.7f, 0.15f, 1.0f });
        }
        ImGui::Button(&_ECSManager->getComponent<TagName>(gameObject).tagName[0]);
        if (gameObject == gameObjectSelected)
        {
            ImGui::PopStyleColor(2);
        }
        
        if (ImGui::IsItemClicked())
        {
            
            gameObjectSelected = gameObject;
            
            info = _ECSManager->getInfoGameObject(gameObjectSelected);
            firstTime = true;
            selected = true;
        }
    }
    
    ImGui::Begin("Properties");
    if (selected)
    {
        ImGui::InputText(" ", &_ECSManager->getComponent<TagName>(gameObjectSelected).tagName[0], 30); // (label, tagName, size)
        if (ImGui::Button("Add Component"))
                ImGui::OpenPopup("AddComponent");
                if (ImGui::BeginPopup("AddComponent"))
                {
                        
                        if (ImGui::MenuItem("Transform"))
                        {
                            if(!info.test(1))
                            {
                                _ECSManager->addComponent(gameObjectSelected, TransformComponent{});
                                info = _ECSManager->getInfoGameObject(gameObjectSelected);
                            }
                            
                            ImGui::CloseCurrentPopup();
                        }
                    
                        if (ImGui::MenuItem("Modelo"))
                        {
                            // File open
                            auto f = pfd::open_file("Choose model file", "",
                                                    { "Model Files (.obj .obj)", "*.obj *.obj",
                                                      "All Files", ".obj" });

                            if(f.result().size() != 0)
                            {
                                std::string ruta = f.result()[0];
                                if (!info.test(2))
                                {
                                    _ECSManager->addComponent(gameObjectSelected, Model{.modelo = Modelo(ruta)}); // Load the model data, this load job should be in an specific class.
                                    _ECSManager->getComponent<Model>(gameObjectSelected).ruta = ruta;
                                    info = _ECSManager->getInfoGameObject(gameObjectSelected);
                                }
                            }

                            ImGui::CloseCurrentPopup();
                            
                        }
                        if (ImGui::MenuItem("DirectionalLight"))
                        {
                            if(!info.test(3))
                            {
                                _ECSManager->addComponent(gameObjectSelected, DirectionalLightComponent{});
                                info = _ECSManager->getInfoGameObject(gameObjectSelected);
                            }
                            ImGui::CloseCurrentPopup();
                        }
                        if (ImGui::MenuItem("PointLight"))
                        {
                            if(!info.test(4))
                            {
                                _ECSManager->addComponent(gameObjectSelected, PointLightComponent{});
                                info = _ECSManager->getInfoGameObject(gameObjectSelected);
                            }
                            ImGui::CloseCurrentPopup();
                        }
                        if (ImGui::MenuItem("SpotLight"))
                        {
                            if(!info.test(5))
                            {
                                _ECSManager->addComponent(gameObjectSelected, SpotLightComponent{});
                                info = _ECSManager->getInfoGameObject(gameObjectSelected);
                            }
                            ImGui::CloseCurrentPopup();
                        }
                        if (ImGui::MenuItem("Weapon"))
                        {
                            if(!info.test(6))
                            {
                                _ECSManager->addComponent(gameObjectSelected, WeaponComponent{});
                                info = _ECSManager->getInfoGameObject(gameObjectSelected);
                            }
                            ImGui::CloseCurrentPopup();
                        }
                    if (ImGui::MenuItem("Projectile"))
                    {
                        if(!info.test(7))
                        {
                            _ECSManager->addComponent(gameObjectSelected, ProjectileComponent{});
                            info = _ECSManager->getInfoGameObject(gameObjectSelected);
                        }
                        ImGui::CloseCurrentPopup();
                    }
                        if (ImGui::MenuItem("Health"))
                        {
                            ImGui::CloseCurrentPopup();
                        }
                        

                    ImGui::EndPopup();
                }
        components();
    }
    
    ImGui::End();
    ImGui::End();
}

void ImGuiMy::components()
{
    if(info.test(1)) // TransformComponent
    {
        auto& transform = _ECSManager->getComponent<TransformComponent>(gameObjectSelected);
        vec3Drag("Translation", transform.Translation, 0.0f, 100.0f);
//        glm::vec3 rotation = glm::degrees(transform.Rotation);
        
        
//        if (firstTime)
//        {
//            rotation = transform.RotEuler;//glm::degrees(mth::QuatToEuler(transform.Rotation));
//            firstTime = false;
//        }
        rotation = transform.RotEuler;
        vec3Drag("Rotation", rotation, 0.0f, 100.0f);
        if (rotationChanging)
        {
            rotationDelta = transform.RotEuler;
            transform.RotEuler = rotation;
            rotationDelta = rotationDelta - transform.RotEuler;
            rotationDelta = mth::toRadians(rotationDelta);
            mth::Quatern q1 = mth::EulerToQuat(rotationDelta.x, rotationDelta.y, rotationDelta.z);
            transform.Rotation = transform.Rotation * q1;
        }
//        else if(released == true)
//        {
//
//
//            released = false;
//        }
//        if(released)
//        {
//            transform.RotEuler = glm::degrees(mth::QuatToEuler(transform.Rotation));
//            rotation = glm::degrees(mth::QuatToEuler(transform.Rotation));
//            released = false;
//        }
        
        
//        rotation = glm::radians(rotation);
//
//        transform.RotEuler = rotation - transform.RotEuler;
//        mth::Quatern q1 = mth::EulerToQuat(transform.RotEuler.x, transform.RotEuler.y, transform.RotEuler.z);
////        q1 = q1 - transform.Rotation;
//        transform.Rotation = q1 * transform.Rotation;
////        transform.Rotation = glm::radians(rotation);
//
            
        vec3Drag("Scale", transform.Scale, 0.0f, 100.0f);
    }
    
    if(info.test(2)) // _ECSManager->getComponentType<Model>()
    {
        ImGui::Text("Model");
        std::string path = _ECSManager->getComponent<Model>(gameObjectSelected).ruta;
        ImGui::SameLine();
        ImGui::Text(path.substr(path.find_last_of("/\\") + 1).c_str());
    }
    
    if(info.test(3))
    {
        auto& lightComponent = _ECSManager->getComponent<DirectionalLightComponent>(gameObjectSelected);
        vec3Drag("LightColor", lightComponent.lightColor, 0.0f, 100.0f);
        dragFloat("Diffuse Intensity", lightComponent.diffuseIntensity, 100.0f, 1.0f);
        dragFloat("Ambient Intensity", lightComponent.ambientIntensity, 100.0f, 1.0f);
    }
    
    if(info.test(4))
    {
        auto& lightComponent = _ECSManager->getComponent<PointLightComponent>(gameObjectSelected);
        vec3Drag("LightColor", lightComponent.lightColor, 0.0f, 100.0f);
        dragFloat("Diffuse Intensity", lightComponent.diffuseIntensity, 100.0f, 1.0f);
        dragFloat("Radius", lightComponent.maxRadius, 100.0f, 100.0f);
    }
    
    if(info.test(5))
    {
        auto& lightComponent = _ECSManager->getComponent<SpotLightComponent>(gameObjectSelected);
        vec3Drag("LightColor", lightComponent.lightColor, 0.0f, 100.0f);
        dragFloat("Diffuse Intensity", lightComponent.diffuseIntensity, 100.0f, 1.0f);
        dragFloat("Radius", lightComponent.maxRadius, 100.0f, 100.0f);
    }
    
    if(info.test(6))
    {
        ImGui::Text("Weapon");
    }
    
    if(info.test(7))
    {
        ImGui::Text("Projectile");
    }

}
void ImGuiMy::dragFloat(const std::string& label, float& value, float columWidth, float dragMaxValue)
{
    ImGui::PushID(label.c_str());
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, 150.0f);
    ImGui::Text(label.c_str());
    ImGui::NextColumn();
    ImGui::PushItemWidth(300.0f);
    ImGui::DragFloat("##A", &value, 0.1f, 0.0f, dragMaxValue, "%.2f");
    ImGui::PopItemWidth();
    ImGui::Columns(1);
    ImGui::PopID();
    
    
}
void ImGuiMy::vec3Drag(const std::string& label, mth::Vector3& values, float resetValue, float columWidth)
{
    float minValue = 0.0f;
    float maxValue = 0.0f;
    float stepValue = 0.1f;
    std::string buttonLabelX = "X";
    std::string buttonLabelY = "Y";
    std::string buttonLabelZ = "Z";
    if (label == "LightColor")
    {
        minValue = 0.0f;
        maxValue = 1.0f;
        stepValue = 0.01f;
        buttonLabelX = "R";
        buttonLabelY = "G";
        buttonLabelZ = "B";
    }
    
    ImGui::PushID(label.c_str());
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, 100.0f);
    ImGui::Text(label.c_str());
    ImGui::NextColumn();
    
    ImGui::PushItemWidth(100.0f);
    ImGui::PushItemWidth(100.0f);
    ImGui::PushItemWidth(100.0f);
    
    if (selected)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.7f, 0.1f, 0.15f, 1.0f });
        ImGui::Button(buttonLabelX.c_str());
        ImGui::PopStyleColor(1);
        ImGui::SameLine();
        rotationChanging = ImGui::DragFloat("##X", &values.x, stepValue, minValue, maxValue, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();
        
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.3f, 0.9f, 0.15f, 0.8f });
        ImGui::Button(buttonLabelY.c_str());
        ImGui::PopStyleColor(1);
        ImGui::SameLine();
        rotationChanging += ImGui::DragFloat("##Y", &values.y, stepValue, minValue, maxValue, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();
        
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.1f, 0.9f, 1.0f });
        ImGui::Button(buttonLabelZ.c_str());
        ImGui::PopStyleColor(1);
        ImGui::SameLine();
        rotationChanging += ImGui::DragFloat("##Z", &values.z, stepValue, minValue, maxValue, "%.2f");
        ImGui::PopItemWidth();
    }
    ImGui::Columns(1);
    ImGui::PopID();
}
void ImGuiMy::initGuizmo()
{
    ImGuizmo::SetOrthographic(false);
    if (selected)
    {
        auto& transform = _ECSManager->getComponent<TransformComponent>(gameObjectSelected);

//        ImGuizmo::RecomposeMatrixFromComponents(&transform.Translation.x, &transform.Rotation.x, &transform.Scale.x, glm::value_ptr(Transform));
        mth::Matrix4 Transform = mth::translate(mth::Matrix4(1.0f), transform.Translation) * mth::RotationM4(transform.Rotation) * mth::scale(mth::Matrix4(1.0f), transform.Scale);
        ImGuizmo::Manipulate(glm::value_ptr(_camera->getView()), glm::value_ptr(_camera->getProjection()),
                             ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::MODE::LOCAL, mth::Mat4Point(Transform));
//                            nullptr, snap ? snapValues : nullptr);

        //Rotation
        /*Rotation requires to create a custom method to decompose the matrix, because de default doesnt work*/
//        ImGuizmo::Manipulate(glm::value_ptr(_camera->getView()), glm::value_ptr(_camera->getProjection()),
//                            ImGuizmo::OPERATION::ROTATE, ImGuizmo::MODE::WORLD, glm::value_ptr(Transform));
        
        //Scale
//        ImGuizmo::Manipulate(glm::value_ptr(_camera->getView()), glm::value_ptr(_camera->getProjection()),
//                            ImGuizmo::OPERATION::SCALE, ImGuizmo::MODE::WORLD, glm::value_ptr(Transform));
        
        if (ImGuizmo::IsUsing()) {
            glm::vec3 trans;
            glm::vec3 rot;
            glm::vec3 scale;
            
            ImGuizmo::DecomposeMatrixToComponents(mth::Mat4Point(Transform), glm::value_ptr(trans), glm::value_ptr(rot), glm::value_ptr(scale));
            
            transform.Translation = trans;
//            transform.Rotation = rot;
//            transform.Rotation = scale;
        }
    }

}
