/**
 * @file Core.h
 * @author flexhaufen
 * @brief core of the engine
 * @version 0.1
 * @date 2022-09-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/Core/Layer/Layer.h"
#include "Lychee/Core/Layer/LayerStack.h"
#include "Lychee/Core/Time/DeltaTime.h"
#include "Lychee/Core/Window/Window.h"
#include "Lychee/Core/Vulkan/vkhManager.h"


#include "Lychee/Events/Event.h"
#include "Lychee/Events/ApplicationEvent.h"

#include "Lychee/ImGui/ImGuiLayer.h"
// *** DEFINES ***


// *** NAMESPACE ***
namespace Lychee {

    /**
     * @brief Core
     * 
     */
    class Core {

    public:

        /**
         * @brief Construct a new Core object
         * 
         */
        Core();

        /**
         * @brief Destroy the Core object
         * 
         */
        ~Core();

        /**
         * @brief Running loop
         * 
         */
        void Run();

        /**
         * @brief Closes App
         * 
         */
        void Close();

        /**
         * @brief Event Handling
         * 
         */
        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        /**
         * @brief Get the ImGuiLayer instance
         * 
         * @return ImGuiLayer* 
         */
        ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

        /**
         * @brief Gets Core instance
         * 
         * @return Core& 
         */
        static Core& Get() { return *s_Instance; }

        /**
         * @brief Get the Window instance
         * 
         * @return Window& 
         */
        Window& GetWindow() { return *m_Window; }

    private:
        /**
         * @brief Window close event
         * 
         * @param e Event
         * @return true if window is closed
         */
        bool OnWindowClose(WindowCloseEvent& e);

        /**
         * @brief Window resize event
         * 
         * @param e Event
         * @return true if window is rezised 
         */
        bool OnWindowResize(WindowResizeEvent& e);

        // TODO (flex): setup splashscreen
        //void OnSplashScreenDisplay();

    private:
        // ** Members **
        static Core* s_Instance;    // Instance of core - for external usage
        
        bool m_isRunning = true;    // True when app is running
        bool m_isMinimized = false; // True when app is minimzed
        
        Window* m_Window;           // Window
        vkhManager m_vkhManager;    // Vulkan abstraction
        
        float m_lastFrameTime;      // delta time

        // * Random ass layers *
        ImGuiLayer* m_ImGuiLayer;   // Imgui
        LayerStack m_LayerStack;    // Layerstack
    };
}