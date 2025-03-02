/**
 * @file Renderer.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-03-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// *** INCLUDES ***
#include "Lychee/lypch.h"

#include "Lychee/Renderer/Renderer.h"

// *** DEFINE ***

// *** NAMESPACE ***
namespace Lychee {
    
    // *** STATIC ***
    bool Renderer::s_Initialized = false;
    Scope<vkhManager> Renderer::s_vkhManager = CreateScope<vkhManager>();

    // *** FUNCTIONS **
    void Renderer::Init(GLFWwindow* window) {

        if (s_Initialized) {
            LY_CORE_WARN("Renderer: The renderer is already initialized - skipping");
            return;
        }

        s_Initialized = true;

        LY_CORE_INFO("Renderer: Initializing");
        s_vkhManager->setup(window);        
    }

    void Renderer::Terminate() {
        s_Initialized = false;
        s_vkhManager->cleanup();
    }

    //void Renderer::OnWindowResize() {
    //    s_vkhManager->setFrameBufferResized(true);
    //}

    void Renderer::BeginScene() {
        s_vkhManager->beginFrame();
    }

    void Renderer::EndScene() {
        s_vkhManager->endFrame();
    }
}