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

// *** INCLUDES ***
#include "Lychee/lypch.h"

#include "Lychee/Events/Event.h"
#include "Lychee/Events/MouseEvent.h"

#include "Lychee/Core/Time/DeltaTime.h"

// *** DEFIENS ***

// *** NAMESPACE ***
namespace Lychee {

    using EventCallbackFn = std::function<void(Event&)>;


    /**
     * @brief Window Class
     * 
     */
	class Window {
	public:
        
		/**
		 * @brief Construct a new Window object
		 * 
		 * @param title Window title
		 * @param with 	Window width (px)
		 * @param height Window height (px)
		 */
		Window(std::string title, u32 with, u32 height);

		/**
		 * @brief Destroy the Window object
		 * 
		 */
		virtual ~Window();

		/**
		 * @brief Window update function
		 * 
		 */
		void OnUpdate(DeltaTime dt);

		/**
		 * @brief Get the Width
		 * 
		 * @return u32 width
		 */
		u32 GetWidth() const { return m_sWindowData.width; }

		/**
		 * @brief Get the Height
		 * 
		 * @return u32 height
		 */
		u32 GetHeight() const { return m_sWindowData.height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) { m_sWindowData.eventCallback = callback; }
		void SetVSync(bool enabled);
		bool IsVSync() const;

		GLFWwindow* GetNativeWindow() { return m_glfwWindow; }
	private:

		/**
		 * @brief Init window
		 * 
		 */
		void Init();

		/**
		 * @brief Terminate window
		 * 
		 */
		void Terminate();
		
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

		f32 m_elapsedTimeFps = 0.0f;	// Elapsed time since last fps update
		u16 m_frameCounterFps = 0;		// Frames since last fps update
	};
}