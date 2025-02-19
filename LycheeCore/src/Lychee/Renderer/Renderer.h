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
        ~Renderer() {}

        /**
         * @brief Initialize the renderer
         * 
         * @param window  The window to render to
         */
        void Init(GLFWwindow* window);
        void Render();


        void OnResize() { m_vkhManager.setFrameBufferResized(true); }

        /**
         * @brief Wait for the renderer to finish
         * 
         */
        void WaitIdle() { m_vkhManager.waitIdle(); }

        /**
         * @brief Terminate the renderer
         * 
         */
        void Terminate() { m_vkhManager.cleanup(); }


    private:

        vkhManager m_vkhManager;

    };
}