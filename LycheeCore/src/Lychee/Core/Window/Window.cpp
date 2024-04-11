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

// *** INCLUDES ***
#include "Lychee/Core/Window/Window.h"

#include "Lychee/Events/KeyEvent.h"
#include "Lychee/Events/MouseEvent.h"
#include "Lychee/Events/ApplicationEvent.h"

#include "Lychee/Core/Window/vkInstance.h"

// *** DEFINES ***

// *** NAMESPACE ***
namespace Lychee {

	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int32_t error, const char* description) {
		LY_CORE_ERROR("Window: GLFW Error ({0}): {1}", error, description);
	}


	Window::Window(std::string title, uint32_t width, uint32_t height) {
		m_sWindowData.title = title;
		m_sWindowData.width = width;
		m_sWindowData.height = height;
        Init();
	}

	Window::~Window() {
		Terminate();
	}

	void Window::Init() {
		LY_CORE_INFO("Window: Initializing");
		LY_CORE_INFO("Window: \\---- [{0}] ({1}, {2})", m_sWindowData.title, m_sWindowData.width, m_sWindowData.height);
		LY_CORE_INFO("Window: \\---- Initializing GLFW Window");
        if(!glfwInit()){
            LY_CORE_ERROR("Window:       \\---- Failed to initialize GLFW!");
        }

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);	// Disable OpenGL default client
		// TODO: Implement
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);		// Disable window resizeable for now

        glfwSetErrorCallback(GLFWErrorCallback);

		m_glfwWindow = glfwCreateWindow((int32_t)m_sWindowData.width, 
                                        (int32_t)m_sWindowData.height, 
                                        m_sWindowData.title.c_str(), 
                                        nullptr, 
                                        nullptr);

		LY_CORE_INFO("Window: \\---- Initializing Vulkan");
		if (!glfwVulkanSupported()) {
			LY_CORE_ERROR("Window:       \\---- Vulkan not supported!");
		}

		vk::CreateVkInstance(m_sWindowData.title.c_str(), m_vkInstance);

		if (m_instance == nullptr) {
			LY_CORE_ERROR("Window:       \\---- Failed initializing Vulkan!");
		}

		//VkResult vkErr = glfwCreateWindowSurface(m_gl)


		/*
		glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_glfwWindow));
	
		glfwSetWindowUserPointer(m_glfwWindow, &m_sWindowData);




		// TODO (flex): Implement window icon
		// Set window ico
		//GLFWimage glfwWindowIco[1];
		//glfwWindowIco[0].pixels = stbi_load(LY_ICON_PNG, &glfwWindowIco[0].width, &glfwWindowIco[0].height, nullptr, 4);
		//glfwSetWindowIcon(m_glfwWindow, 1, glfwWindowIco) ;

        LY_CORE_INFO("Window: \\---- Setting vsync to {0}", LY_VSYNC_DEFAULT);
		SetVSync(LY_VSYNC_DEFAULT);

		//** Callbacks **
		//* Window Resize *
		glfwSetWindowSizeCallback(m_glfwWindow, [](GLFWwindow* window, int32_t width, int32_t height) {
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
		glfwSetKeyCallback(m_glfwWindow, [](GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods) {
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
		glfwSetCharCallback(m_glfwWindow, [](GLFWwindow* window, uint32_t keycode) {
			sWindowData& data = *(sWindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.eventCallback(event);
		});

		//* Mouse Button *
		glfwSetMouseButtonCallback(m_glfwWindow, [](GLFWwindow* window, int32_t button, int32_t action, int32_t mods) {
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
		glfwSetScrollCallback(m_glfwWindow, [](GLFWwindow* window, double xOffset, double yOffset) {
			sWindowData& data = *(sWindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.eventCallback(event);
		});

		//* Mous Pos *
		glfwSetCursorPosCallback(m_glfwWindow, [](GLFWwindow* window, double xPos, double yPos) {
			sWindowData& data = *(sWindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.eventCallback(event);
		});
		*/
	}

	void Window::Terminate() {
        LY_CORE_INFO("Window: Terminating");
		vk::DestroyInstance(m_vkInstance);
		glfwDestroyWindow(m_glfwWindow);	
        glfwTerminate();
	}

	void Window::OnUpdate(DeltaTime dt) {

		// NOTE: This function may use unnecessary resources.
		//		 It will not be compiled in releas builds.
		#ifdef LY_SHOW_WINDOWTITLE_FPS
			m_elapsedTimeFps += dt.GetSeconds();
			m_frameCounterFps++;

			if (m_elapsedTimeFps >= 1.0f) {
				std::string title =  m_sWindowData.title + " FPS:  " + std::to_string(m_frameCounterFps);
				glfwSetWindowTitle(m_glfwWindow, title.c_str());	
				m_frameCounterFps = 0;
				m_elapsedTimeFps = 0;
			}
		#endif

		glfwPollEvents();
		glfwSwapBuffers(static_cast<GLFWwindow*>(m_glfwWindow));
	}

	void Window::SetVSync(bool enabled) {
        glfwSwapInterval(int32_t(enabled));
		m_sWindowData.isVSyncOn = enabled;
	}

	bool Window::IsVSync() const {
		return m_sWindowData.isVSyncOn;
	}

}
