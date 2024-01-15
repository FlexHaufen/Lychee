/**
 * @file Window.cpp
 * @author flexhaufen
 * @brief Window of app
 * @version 0.1
 * @date 2022-09-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//*** INCLUDES ***
#include "Lychee/Core/Window/Window.h"

//*** DEFINES ***

//*** NAMESPACE ***
namespace Lychee {

//static u8 s_GLFWWindowCount = 0;

	/*
	static void GLFWErrorCallback(s32 error, const c8* description) {
		LY_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}
	*/

	Window::Window(std::string title, u32 width, u32 height) {
		m_sWindowData.title = title;
		m_sWindowData.width = width;
		m_sWindowData.height = height;
        Init();
	}

	Window::~Window() {
		Terminate();
	}

	void Window::Init() {
	
		LY_CORE_INFO("Initializing window: {0} ({1}, {2})", m_sWindowData.title, m_sWindowData.width, m_sWindowData.height);

		LY_CORE_INFO("Initializing SFML Window");
        m_Window.create(sf::VideoMode(m_sWindowData.width, m_sWindowData.height), m_sWindowData.title);

		// Set window ico
		auto windowIcon = sf::Image();
		if (!windowIcon.loadFromFile(LY_ICON_PNG)) {
			LY_CORE_WARN("Could not load window icon at [{0}]", LY_ICON_PNG);
		}
		else {
			m_Window.setIcon(windowIcon.getSize().x, windowIcon.getSize().y, windowIcon.getPixelsPtr());
		}
		

        LY_CORE_INFO("Setting vsync to {0}", LY_VSYNC_DEFAULT);
		SetVSync(LY_VSYNC_DEFAULT);


		// TODO (flex): Window callbacks
		//** Callbacks **
		//* Window Resize *
		/*
		glfwSetWindowSizeCallback(m_glfwWindow, [](GLFWwindow* window, s32 width, s32 height) {
			sWindowData& data = *(sWindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;
			WindowResizeEvent event(width, height);
			data.eventCallback(event);
		});

		//* Window Close *
		glfwSetWindowCloseCallback(m_glfwWindow, [](GLFWwindow* window) {
			sWindowData& data = *(sWindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.eventCallback(event);
		});

		//* Keys *
		glfwSetKeyCallback(m_glfwWindow, [](GLFWwindow* window, s32 key, s32 scancode, s32 action, s32 mods) {
			sWindowData& data = *(sWindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent event(key, 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:{
					KeyReleasedEvent event(key);
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(key, true);
					data.eventCallback(event);
					break;
				}
			}
		});

		//* Char *
		glfwSetCharCallback(m_glfwWindow, [](GLFWwindow* window, u32 keycode) {
			sWindowData& data = *(sWindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.eventCallback(event);
		});

		//* Mouse Button *
		glfwSetMouseButtonCallback(m_glfwWindow, [](GLFWwindow* window, s32 button, s32 action, s32 mods) {
			sWindowData& data = *(sWindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.eventCallback(event);
					break;
				}
			}
		});

		//* Mouse Scroll *
		glfwSetScrollCallback(m_glfwWindow, [](GLFWwindow* window, f64 xOffset, f64 yOffset) {
			sWindowData& data = *(sWindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((f32)xOffset, (f32)yOffset);
			data.eventCallback(event);
		});

		//* Mous Pos *
		glfwSetCursorPosCallback(m_glfwWindow, [](GLFWwindow* window, f64 xPos, f64 yPos) {
			sWindowData& data = *(sWindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((f32)xPos, (f32)yPos);
			data.eventCallback(event);
		});
		*/

	}

	void Window::Terminate() {
        LY_CORE_INFO("Terminating window");
		m_Window.close();
	}

	void Window::OnUpdate(DeltaTime dt) {

		// NOTE: This function may use unnecessary resources.
		//		 It will not be compiled in releas builds.
		#ifdef LY_SHOW_WINDOWTITLE_FPS
			m_elapsedTimeFps += dt.GetSeconds();
			m_frameCounterFps++;

			if (m_elapsedTimeFps >= 1.0f) {
				std::string title =  m_sWindowData.title + " FPS:  " + std::to_string(m_frameCounterFps);
				m_Window.setTitle(title);
				m_frameCounterFps = 0;
				m_elapsedTimeFps = 0;
			}
		#endif
		m_Window.clear(LY_SCENE_CLEAR_BACKGROUND);
	}

	void Window::SetVSync(bool enabled) {
		m_Window.setVerticalSyncEnabled(enabled);
		m_sWindowData.isVSyncOn = enabled;
	}

	bool Window::IsVSync() const {
		return m_sWindowData.isVSyncOn;
	}

}
