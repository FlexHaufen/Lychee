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
# pragma once

// *** INCLUDES ***
#include "Lychee/lypch.h"

#include "Lychee/Core/Layer/LayerStack.h"
#include "Lychee/Core/Time/Deltatime.h"
#include "Lychee/Core/Window/Window.h"

#include "Lychee/Events/EventManager.h"
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
         * @param isSplashScreenEnabled     true enable splash screen
         */
        Core(b8 isSplashScreenEnabled = false);

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
        void OnEvent(sf::Event& e);


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
        b8 OnWindowClose(sf::Event& e);
	    b8 OnWindowResize(sf::Event& e);

        void OnSplashScreenDisplay();

    private:
        // ** Members **
        static Core* s_Instance;    // Instance of core - for external usage
        
        bool m_isRunning = true;    // True when app is running
        bool m_isMinimized = false; // True when app is minimzed
        Window* m_Window;           // Window
        
        DeltaTime m_dt;             // delta time

        // * Random ass layers *
        ImGuiLayer* m_ImGuiLayer;   // Imgui
        LayerStack m_LayerStack;    // Layerstack
    };
}