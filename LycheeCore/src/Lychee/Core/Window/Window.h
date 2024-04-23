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
	 * @brief Vulkan window struct
	 * 
	 */
	struct sVkWindow {
		// Instance related
		vk::Instance Instance = nullptr;
		vk::DebugUtilsMessengerEXT DebugMessenger = nullptr;
		vk::DispatchLoaderDynamic DispatchLoaderD;
		vk::SurfaceKHR Surface;

		// Device related
		vk::PhysicalDevice PhysicalDevice = nullptr;
		vk::Device LogicalDevice = nullptr;
		vk::Queue GraphicsQueue = nullptr;
		vk::Queue PresentQueue = nullptr;
	};


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

		GLFWwindow* GetNativeGlfwWindow() { return m_glfwWindow; }
		sVkWindow& GetNativeVkWindow() { return m_vkWindow; }

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
			uint32_t width, height;
			bool isVSyncOn;

			EventCallbackFn eventCallback;
		} m_WindowData;

		sVkWindow m_vkWindow;

		float m_elapsedTimeFps = 0.0f;	// Elapsed time since last fps update
		uint16_t m_frameCounterFps = 0;		// Frames since last fps update
	};
}