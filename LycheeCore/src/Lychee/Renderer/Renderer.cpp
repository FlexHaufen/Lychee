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
    
    void Renderer::Init(GLFWwindow* window) {
        LY_CORE_INFO("Renderer: Initializing");
        m_vkhManager.setup(window);        
    }

    void Renderer::Render() {
        m_vkhManager.drawFrame();
    }
}