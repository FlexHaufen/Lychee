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
#include "Lychee/Renderer/Vulkan/vkhManager.h"



// *** NAMESPACE ***
namespace Lychee {


    class Renderer {
    public:

        /**
         * @brief Initialize the renderer
         * 
         * @param window  The window to render to
         */
        static void Init(GLFWwindow* window);
        
        /**
         * @brief Terminate the renderer
         * 
         */
        static void Terminate();

        // static void OnWindowResize();

        static void BeginScene();
        static void EndScene();

    private:

        static bool s_Initialized;
        static Scope<vkhManager> s_vkhManager;

    };
}