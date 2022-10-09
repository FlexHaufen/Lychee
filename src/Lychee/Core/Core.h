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

// ** Window **
#include "Lychee/Core/Window/Window.h"

//** Events **
#include "Lychee/Events/KeyEvent.h"
#include "Lychee/Events/ApplicationEvent.h"

//** Time **
#include "Lychee/Core/Time/Deltatime.h"

//** Layers **
#include "Lychee/Core/Layer/LayerStack.h"

//** ImGui **
#include "Lychee/ImGui/ImGuiLayer.h"

//*** DEFINES ***


//*** NAMESPACE ***
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
             * @param e Event
             */
            void OnEvent(Event& e);


            void PushLayer(Layer* layer);
            void PushOverlay(Layer* layer);

            // TODO: Describe this stuff
            ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
		    static Core& Get() { return *s_Instance; }
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
    private:
        // *** MEMBERS ***7
        static Core* s_Instance;    // Instance of core - for external usage
        
        bool m_isRunning = true;    // True when app is running
        bool m_isMinimized = false; // True when app is minimzed
        Window* m_Window;           // Window
        
        f32 m_lastFrameTime = 0.0f; // Last frame time

        // * Random ass layers *
        ImGuiLayer* m_ImGuiLayer;   // Imgui
        LayerStack m_LayerStack;    // Layerstack
    };
}