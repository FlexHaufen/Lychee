/**
 * @file Window.h
 * @author flaxhaufen
 * @brief Window of app
 * @version 0.1
 * @date 2022-09-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

//*** INCLUDES ***
#include "Lychee/lypch.h"
//** Events **
#include "Lychee/Events/Event.h"



//*** DEFIENS ***

//*** NAMESPACE ***
namespace Lychee {

     using EventCallbackFn = std::function<void(Event&)>;


    /**
     * @brief Window Class
     * 
     */
	class Window {
	public:
        /**
         * @brief Construct a new Windows Window object
         * 
         * @param props Window properties
         */
		Window(std::string title, u32 with, u32 height);
		virtual ~Window();

		void OnUpdate();

		u32 GetWidth() const { return m_sWindowData.width; }
		u32 GetHeight() const { return m_sWindowData.height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) { m_sWindowData.eventCallback = callback; }
		void SetVSync(bool enabled);
		bool IsVSync() const;

		void* GetNtiveWindow() const { return m_glfwWindow; }

	private:
		void Init();
		void Shutdown();
	private:

        //** Members **
		GLFWwindow* m_glfwWindow; // GLFW Window
		
		/**
		 * @brief Data of window
		 * 
		 */
		struct sWindowData {
			std::string title;
			u32 width, height;
			bool isVSyncOn;

			EventCallbackFn eventCallback;
		};

		sWindowData m_sWindowData;	  // Window data


        // TODO: Implement later
        //Scope<GraphicsContext> m_Context;
		
	};

}