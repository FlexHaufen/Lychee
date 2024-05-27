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
#include <string>
#include <functional>

#include <GLFW/glfw3.h>

#include "Lychee/Events/Event.h"
#include "Lychee/Core/Time/DeltaTime.h"
#include "Lychee/Core/Vulkan/vkhManager.h"

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
		Window(std::string title, uint32_t with, uint32_t height);

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
		uint32_t GetWidth() const { return m_WindowData.width; }

		/**
		 * @brief Get the Height
		 * 
		 * @return u32 height
		 */
		uint32_t GetHeight() const { return m_WindowData.height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) { m_WindowData.eventCallback = callback; }
		void SetVSync(bool enabled);
		bool IsVSync() const;

		void WaitIdle() { m_vkhManager.waitIdle(); }


		GLFWwindow* GetNativeGlfwWindow() { return m_glfwWindow; }

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
		// Window functions and members
        GLFWwindow* m_glfwWindow = nullptr;

		vkhManager m_vkhManager;

		/**
		 * @brief Data of window
		 * 
		 */
		struct sWindowData {
			std::string title;
			uint32_t width, height;
			bool isVSyncOn;

			EventCallbackFn eventCallback;
		} m_WindowData;

		float m_elapsedTimeFps = 0.0f;	// Elapsed time since last fps update
		uint16_t m_frameCounterFps = 0;		// Frames since last fps update
	};
}