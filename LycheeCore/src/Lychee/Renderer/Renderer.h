/**
 * @file Renderer.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-03-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/Core/Vulkan/vkhManager.h"



// *** NAMESPACE ***
namespace Lychee {

    class Renderer {
    public:
        Renderer() {}
        ~Renderer() { Terminate(); }

        void Init(GLFWwindow* window);
        void Render();

        void OnResize() { m_vkhManager.setFrameBufferResized(true); }
        void WaitIdle() { m_vkhManager.waitIdle(); }
        void Terminate() { m_vkhManager.cleanup(); }


    private:

        vkhManager m_vkhManager;

    };
}